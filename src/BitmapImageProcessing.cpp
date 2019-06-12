#include "../include/BitmapImageProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

BitmapImageProcessing::BitmapImageProcessing(
    const char *_inImgName,
    const char *_outImgName,
    int *_height,
    int *_width,
    int *_bitDepth,
    unsigned char *_header,
    unsigned char *_colorTable,
    unsigned char *_inBuffer,
    unsigned char *_outBuffer)
{
  inImgName = _inImgName;
  outImgName = _outImgName;
  height = _height;
  width = _width;
  bitDepth = _bitDepth;
  header = _header;
  colorTable = _colorTable;
  inBuffer = _inBuffer;
  outBuffer = _outBuffer;
}

void BitmapImageProcessing::readImage()
{
  int i;
  FILE *streamIn;
  streamIn = fopen(inImgName, "rb");

  if (streamIn == (FILE *)0)
  {
    cout << "Unable to open file. Maybe file does not exist" << endl;
    exit(0);
  }

  for (i = 0; i < BMP_HEADER_SIZE; i++)
  {
    header[i] = getc(streamIn);
  }

  *width = *(int *)&header[BMP_WIDTH_HEADER_OFFSET];       // read the width from bitmap header
  *height = *(int *)&header[BMP_HEIGHT_HEADER_OFFSET];     // read the height from bitmap header
  *bitDepth = *(int *)&header[BMP_BITDEPTH_HEADER_OFFSET]; // read the bit Depth from bitmap header

  if (*bitDepth <= 8)
  {
    fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
  }

  fread(inBuffer, sizeof(unsigned char), _512by512_IMG_SIZE, streamIn);
  fclose(streamIn);
}

void BitmapImageProcessing::writeImage()
{
  FILE *outputFile = fopen(outImgName, "wb");
  fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, outputFile);

  if (*bitDepth <= 8)
  {
    fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, outputFile);
  }

  fwrite(outBuffer, sizeof(unsigned char), _512by512_IMG_SIZE, outputFile);
  fclose(outputFile);
}

void BitmapImageProcessing::copyImgData(unsigned char *_srcBuffer, unsigned char *_destBuffer, int bufferSize)
{
  for (int i = 0; i < bufferSize; i++)
  {
    _destBuffer[i] = _srcBuffer[i];
  }
}

void BitmapImageProcessing::binarizeImage(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int threshold)
{
  for (int i = 0; i < imgSize; i++)
  {
    _outImgData[i] = (_inImgData[i] > threshold) ? WHITE : BLACK;
  }
}

BitmapImageProcessing::~BitmapImageProcessing()
{
  //dtor
}
