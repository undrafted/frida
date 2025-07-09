#ifndef FRIDABITMAP_H
#define FRIDABITMAP_H

// --- Bitmap Constants ---
constexpr int _512by512_IMG_SIZE         = 262144;
constexpr int BMP_COLOR_TABLE_SIZE       = 1024;
constexpr int BMP_HEADER_SIZE            = 54;
constexpr int BMP_WIDTH_HEADER_OFFSET    = 18;
constexpr int BMP_HEIGHT_HEADER_OFFSET   = 22;
constexpr int BMP_BITDEPTH_HEADER_OFFSET = 28;
constexpr int MAX_COLOR                  = 255;
constexpr int MIN_COLOR                  = 0;
constexpr int WHITE                      = MAX_COLOR;
constexpr int BLACK                      = MIN_COLOR;
constexpr int GRAYLEVELS_NUM             = 256; // 0-255

// --- FridaBitmap Class ---
class FridaBitmap {
public:
    FridaBitmap(const char* _inImgName,
                const char* _outImgName,
                int* _height,
                int* _width,
                int* _bitDepth,
                unsigned char* _header,
                unsigned char* _colorTable,
                unsigned char* _inBuffer,
                unsigned char* _outBuffer);

    void readImage();
    void writeImage();
    void copyImgData(unsigned char* _srcBuffer, unsigned char* _destBuffer, int bufferSize);
    void binarizeImage(unsigned char* _inImgData, unsigned char* _outImgData, int imgSize, int threshold);
    void adjustBrightness(unsigned char* _inputImgData, unsigned char* _outputImgData, int imgSize, int adjustment);
    void computeHistogram(unsigned char* _imgData, int imgRows, int imgCols, float hist[], const char* histFileName);
    void equalizeHistogram(unsigned char* _inputImgData, unsigned char* _outputImgData, int imgRows, int imgCols);

    virtual ~FridaBitmap();

private:
    const char* inImgName;
    const char* outImgName;
    int* height;
    int* width;
    int* bitDepth;
    unsigned char* header;
    unsigned char* colorTable;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
};

#endif // FRIDABITMAP_H