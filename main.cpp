#include <iostream>
#include "include/BitmapImageProcessing.h"

int main() {
  int imgWidth;
  int imgHeight;
  int imgBitDepth;
  unsigned char imgHeader[BMP_HEADER_SIZE];
  unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
  unsigned char imgInBuffer[_512by512_IMG_SIZE];
  unsigned char imgOutBuffer[_512by512_IMG_SIZE];

  const char imgName[] = "images/image.bmp";
  // const char newImageName[] = "images/output/image_copy.bmp";
  // const char newImageName[] = "images/output/image_b&w.bmp";
  const char newImageName[] = "images/output/image_brightenup.bmp";

  BitmapImageProcessing *image = new BitmapImageProcessing(imgName,
                                                           newImageName,
                                                           &imgHeight,
                                                           &imgWidth,
                                                           &imgBitDepth,
                                                           &imgHeader[0],
                                                           &imgColorTable[0],
                                                           &imgInBuffer[0],
                                                           &imgOutBuffer[0]);

  // image->readImage();
  // image->copyImgData(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE);
  // image->writeImage();
  // std::cout << "Image succesfully copied!" << std::endl;
  // std::cout << "Image height: " << imgHeight << std::endl;
  // std::cout << "Image width: " << imgWidth << std::endl;

  // image->readImage();
  // image->binarizeImage(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, 64);
  // image->writeImage();
  // std::cout << "Image succesfully copied and binarized!" << std::endl;

  int adjustment = 50;
  image->readImage();
  image->adjustBrightness(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, adjustment);
  image->writeImage();
  std::cout << "Image succesfully copied and " <<  ((adjustment > 0) ? "brightened" : "darkened") << "!" << std::endl;

  return 0;
}
