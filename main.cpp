#include <iostream>
#include "include/BitmapImageProcessing.h"

using namespace std;

int main()
{
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
  // cout << "Image succesfully copied!" << endl;
  // cout << "Image height: " << imgHeight << endl;
  // cout << "Image width: " << imgWidth << endl;

  // image->readImage();
  // image->binarizeImage(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, 64);
  // image->writeImage();
  // cout << "Image succesfully copied and binarized!" << endl;

  image->readImage();
  image->brightnessUp(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, 50);
  image->writeImage();
  cout << "Image succesfully copied and brightened up!" << endl;

  return 0;
}
