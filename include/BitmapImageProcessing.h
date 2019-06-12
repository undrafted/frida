#ifndef BITMAPIMAGEPROCESSING_H
#define BITMAPIMAGEPROCESSING_H

static const int _512by512_IMG_SIZE = 262144;
static const int BMP_COLOR_TABLE_SIZE = 1024;
static const int BMP_HEADER_SIZE = 54;
static const int BMP_WIDTH_HEADER_OFFSET = 18;
static const int BMP_HEIGHT_HEADER_OFFSET = 22;
static const int BMP_BITDEPTH_HEADER_OFFSET = 28;
static const int MAX_COLOR = 255;
static const int MIN_COLOR = 0;
static const int WHITE = MAX_COLOR;
static const int BLACK = MIN_COLOR;

class BitmapImageProcessing
{
public:
  BitmapImageProcessing(
      const char *_inImgName,
      const char *_outImgName,
      int *_height,
      int *_width,
      int *_bitDepth,
      unsigned char *_header,
      unsigned char *_colorTable,
      unsigned char *_inBuffer,
      unsigned char *_outBuffer);
  void readImage();
  void writeImage();
  void copyImgData(unsigned char *_srcBuffer, unsigned char *_destBuffer, int bufferSize);
  void binarizeImage(unsigned char *_inImgData, unsigned char *_outImgData, int imgSize, int threshold);
  virtual ~BitmapImageProcessing();

protected:
private:
  const char *inImgName;
  const char *outImgName;
  int *height;
  int *width;
  int *bitDepth;
  unsigned char *header;
  unsigned char *colorTable;
  unsigned char *inBuffer;
  unsigned char *outBuffer;
};

#endif // BITMAPIMAGEPROCESSING_H
