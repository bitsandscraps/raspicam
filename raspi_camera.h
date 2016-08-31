#ifndef HOME_PI_RASPICAM_RASPI_CAMERA_H_
#define HOME_PI_RASPICAM_RASPI_CAMERA_H_

#include <pthread.h>
#include <opencv/cv.h>
#include "/home/pi/git/robidouille/raspicam_cv/RaspiCamCV.h"

struct RaspiCamera {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  RaspiCamCvCapture* capture;
  int index_to_use;
  int is_done;
  int is_ready;
  IplImage* images[3];
  int status[3];
};

void FreeImage(struct RaspiCamera* rpic, int index);
int GetImageToUse(struct RaspiCamera* rpic);
void* CameraLoop(void* args);
void TerminateLoop(struct RaspiCamera* rpic);

#endif  // HOME_PI_RASPICAM_RASPI_CAMERA_H_
