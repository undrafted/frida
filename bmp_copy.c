#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *streamIn = fopen("images/image.bmp", "rb");
  FILE *outputFile = fopen("images/image_copy.bmp", "wb");

  if (streamIn == (FILE *)0)
  {
    printf("Unable to open file\n");
  }

  unsigned char header[54];
  unsigned char colorTable[1024];

  for (int i = 0; i < 54; i++)
  {
    header[i] = getc(streamIn);
  }
  // header offset 18 is image width
  int width = *(int *)&header[18];
  // header offset 24 is image height
  int height = *(int *)&header[22];
  // header offset 28 is image bit depth
  int bitDepth = *(int *)&header[28];

  if (bitDepth <= 8)
  {
    fread(colorTable, sizeof(unsigned char), 1024, streamIn);
  }

  unsigned char buffer[height * width];
  fread(buffer, sizeof(unsigned char), (height * width), streamIn);

  fwrite(header, sizeof(unsigned char), 54, outputFile);
  if (bitDepth <= 8)
  {
    fwrite(colorTable, sizeof(unsigned char), 1024, outputFile);
  }
  fwrite(buffer, sizeof(unsigned char), (height * width), outputFile);

  fclose(outputFile);
  fclose(streamIn);

  printf("Copy success !\n");
  printf("Width: %d\n", width);
  printf("Height: %d\n", height);

  return 0;
}