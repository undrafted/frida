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
  const char newImageName[] = "images/output/image_copy.bmp";

  BitmapImageProcessing *image = new BitmapImageProcessing(imgName,
                                                           newImageName,
                                                           &imgHeight,
                                                           &imgWidth,
                                                           &imgBitDepth,
                                                           &imgHeader[0],
                                                           &imgColorTable[0],
                                                           &imgInBuffer[0],
                                                           &imgOutBuffer[0]);

  image->readImage();
  image->copyImgData(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE);
  image->writeImage();

  cout << "Image succesfully copied!" << endl;
  cout << "Image height: " << imgHeight << endl;
  cout << "Image width: " << imgWidth << endl;

  return 0;
}