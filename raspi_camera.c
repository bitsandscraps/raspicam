#include "/home/pi/raspicam/raspi_camera.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

enum { kFree, kBusy };

int ImageToFill(struct RaspiCamera* rpic);
RaspiCamCvCapture* InitCamera(void);

void FreeImage(struct RaspiCamera* rpic, int index) {
  rpic->status[index] = kFree;
}

int ImageToFill(struct RaspiCamera* rpic) {
  int index;
  pthread_mutex_lock(&rpic->mutex);
  for (index = 0; index < 3; ++index) {
    if (index == rpic->index_to_use) continue;
    if (rpic->status[index] == kFree) break;
  }
  pthread_mutex_unlock(&rpic->mutex);
  return index;
}

RaspiCamCvCapture* InitCamera(void) {
  RaspiCamCvCapture* capture;
  // If we leave a member of config zero, it is set to default.
  RASPIVID_CONFIG * config = (RASPIVID_CONFIG*)calloc(1, sizeof(RASPIVID_CONFIG));
  config->width = 320;
  config->height = 240;
  capture = (RaspiCamCvCapture*)raspiCamCvCreateCameraCapture2(0, config); 
  free(config);
  puts("Waiting until camera stabilizes. It takes about 3 seconds.");
  sleep(3);
  return capture;
}

int GetImageToUse(struct RaspiCamera* rpic) {
  int index;
  index = rpic->index_to_use;
  rpic->status[index] = kBusy;
  return index;
}

void* CameraLoop(void* args) {
  struct RaspiCamera* rpic = args;
  IplImage* image;
  int index;
  rpic->capture = InitCamera();
  image = raspiCamCvQueryFrame(rpic->capture);
  for (index = 0; index < 3; ++index) {
    rpic->status[index] = kFree;
    rpic->images[index] = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
  }
  rpic->index_to_use = 0;
  cvCopy(image, rpic->images[0], NULL);
  // Signal the main loop that it is ready.
  pthread_mutex_lock(&rpic->mutex);
  rpic->is_ready = true;
  pthread_cond_signal(&rpic->cond);
  while (!rpic->is_done) {
    pthread_mutex_unlock(&rpic->mutex);
    image = raspiCamCvQueryFrame(rpic->capture);
    index = ImageToFill(rpic);
    cvCopy(image, rpic->images[index], NULL);
    pthread_mutex_lock(&rpic->mutex);
    rpic->index_to_use = index;
  }
  pthread_mutex_unlock(&rpic->mutex);
	raspiCamCvReleaseCapture(&rpic->capture);
  for (index = 0; index < 3; ++index)
    cvReleaseImage(&rpic->images[index]);
  return NULL;
}

void TerminateLoop(struct RaspiCamera* rpic) {
  rpic->is_done = true;
}

