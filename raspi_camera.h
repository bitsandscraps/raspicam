#ifndef HOME_PI_RASPICAM_RASPI_CAMERA_H_
#define HOME_PI_RASPICAM_RASPI_CAMERA_H_

#include <opencv/cv.h>

// struct used to store information about pixels of a certain color
struct ColorDetect {
  // number of pixels of the corresponding color
  int count;
  // the average x coordinate of the corresponding color
  int average_x;
  // the average y coordinate of the corresponding color
  int average_y;
};

void MaskField(IplImage *mask, IplImage *roiImage);
IplImage* ProcessImage(IplImage* source_image);

#endif  // HOME_PI_RASPICAM_RASPI_CAMERA_H_
