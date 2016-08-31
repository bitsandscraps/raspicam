#ifndef HOME_PI_RASPICAM_RASPI_CMAIN_H_
#define HOME_PI_RASPICAM_RASPI_CMAIN_H_

#include <opencv/cv.h>

void MaskField(IplImage *mask, IplImage *roiImage);
IplImage* ProcessImage(IplImage* source_image);

#endif  // HOME_PI_RASPICAM_RASPI_CMAIN_H_
