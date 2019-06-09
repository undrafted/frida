#include <stdio.h>
#include <stdlib.h>

#define BMP_HEADER_SIZE 54
#define BMP_COLOR_TABLE_SIZE 1024
#define CUSTOM_IMG_SIZE 1024 * 1024

void bmpReader(const char *imgName,
               int *_height,
               int *_width,
               int *_bitDepth,
               unsigned char *_header,
               unsigned char *_colorTable,
               unsigned char *_buffer);

void bmpWriter(const char *imgName,
               unsigned char *header,
               unsigned char *colorTable,
               unsigned char *buffer,
               int bitDepth);

int main()
{

  int imgWidth, imgHeight, imgBitDepth;
  unsigned char imgHeader[BMP_HEADER_SIZE];
  unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
  unsigned char imgBuffer[CUSTOM_IMG_SIZE];

  const char imgName[] = "images/image2.bmp";
  const char copyImgName[] = "images/image2_copy.bmp";

  bmpReader(imgName, &imgWidth, &imgHeight, &imgBitDepth, imgHeader, imgColorTable, imgBuffer);
  bmpWriter(copyImgName, imgHeader, imgColorTable, imgBuffer, imgBitDepth);

  printf("Copy success!\n");
  return 0;
}

void bmpReader(const char *imgName,
               int *_height,
               int *_width,
               int *_bitDepth,
               unsigned char *_header,
               unsigned char *_colorTable,
               unsigned char *_buffer)
{
  int i;
  FILE *streamIn;
  streamIn = fopen(imgName, "rb");

  if (streamIn == (FILE *)0)
  {
    printf("unable to open image \n");
  }

  for (i = 0; i < 54; i++)
  {
    _header[i] = getc(streamIn);
  }
  *_width = *(int *)&_header[18];    // header offset 18 is image width
  *_height = *(int *)&_header[22];   // header offset 24 is image height
  *_bitDepth = *(int *)&_header[28]; // header offset 28 is image bit depth

  if (*_bitDepth <= 8)
  {
    fread(_colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
  }
  fread(_buffer, sizeof(unsigned char), CUSTOM_IMG_SIZE, streamIn);
  fclose(streamIn);
}

void bmpWriter(const char *imgName,
               unsigned char *header,
               unsigned char *colorTable,
               unsigned char *buffer,
               int bitDepth)
{
  FILE *outputFile = fopen(imgName, "wb");
  fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, outputFile);
  if (bitDepth <= 8)
  {
    fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, outputFile);
  }

  fwrite(buffer, sizeof(unsigned char), CUSTOM_IMG_SIZE, outputFile);
  fclose(outputFile);
}
