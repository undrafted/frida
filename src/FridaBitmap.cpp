#include "../include/FridaBitmap.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

FridaBitmap::FridaBitmap(const char *_inImgName, const char *_outImgName,
                         int *_height, int *_width, int *_bitDepth,
                         unsigned char *_header, unsigned char *_colorTable,
                         unsigned char *_inBuffer, unsigned char *_outBuffer) {
    inImgName   = _inImgName;
    outImgName  = _outImgName;
    height      = _height;
    width       = _width;
    bitDepth    = _bitDepth;
    header      = _header;
    colorTable  = _colorTable;
    inBuffer    = _inBuffer;
    outBuffer   = _outBuffer;
}

void FridaBitmap::readImage() {
    FILE *streamIn = fopen(inImgName, "rb");
    if (!streamIn) {
        std::cout << "Unable to open file. Maybe file does not exist" << std::endl;
        exit(0);
    }

    for (int i = 0; i < BMP_HEADER_SIZE; i++) {
        header[i] = getc(streamIn);
    }

    *width    = *(int *)&header[BMP_WIDTH_HEADER_OFFSET];
    *height   = *(int *)&header[BMP_HEIGHT_HEADER_OFFSET];
    *bitDepth = *(int *)&header[BMP_BITDEPTH_HEADER_OFFSET];

    if (*bitDepth <= 8) {
        fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
    }

    fread(inBuffer, sizeof(unsigned char), _512by512_IMG_SIZE, streamIn);
    fclose(streamIn);
}

void FridaBitmap::writeImage() {
    FILE *outputFile = fopen(outImgName, "wb");
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, outputFile);

    if (*bitDepth <= 8) {
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, outputFile);
    }

    fwrite(outBuffer, sizeof(unsigned char), _512by512_IMG_SIZE, outputFile);
    fclose(outputFile);
}

void FridaBitmap::copyImgData(unsigned char *_srcBuffer,
                              unsigned char *_destBuffer, int bufferSize) {
    for (int i = 0; i < bufferSize; i++) {
        _destBuffer[i] = _srcBuffer[i];
    }
}

void FridaBitmap::binarizeImage(unsigned char *_inImgData,
                                unsigned char *_outImgData, int imgSize,
                                int threshold) {
    for (int i = 0; i < imgSize; i++) {
        _outImgData[i] = (_inImgData[i] > threshold) ? WHITE : BLACK;
    }
}

// The higher the pixel value, the brighter it is; the lower, the darker.
// This implementation does truncation.
void FridaBitmap::adjustBrightness(unsigned char *_inImgData,
                                   unsigned char *_outImgData, int imgSize,
                                   int adjustment) {
    for (int i = 0; i < imgSize; i++) {
        int temp = _inImgData[i] + adjustment;
        if (temp > MAX_COLOR) {
            _outImgData[i] = MAX_COLOR;
        } else if (temp < MIN_COLOR) {
            _outImgData[i] = MIN_COLOR;
        } else {
            _outImgData[i] = temp;
        }
    }
}

void FridaBitmap::computeHistogram(unsigned char *_imgData, int imgRows,
                                   int imgCols, float hist[],
                                   const char *histFileName) {
    FILE *fptr = fopen(histFileName, "w");
    long int ihist[256] = {0};
    long int sum = 0;

    for (int y = 0; y < imgRows; y++) {
        for (int x = 0; x < imgCols; x++) {
            int j = *(_imgData + x + y * imgCols);
            ihist[j]++;
            sum++;
        }
    }
    for (int i = 0; i < 255; i++) {
        hist[i] = (float)ihist[i] / (float)sum;
    }

    // Write content to txt file
    for (int i = 0; i <= 255; i++) {
        fprintf(fptr, "\n%f", hist[i]);
    }

    fclose(fptr);
}

void FridaBitmap::equalizeHistogram(unsigned char *_inputImgData,
                                    unsigned char *_outputImgData, int imgRows,
                                    int imgCols) {
    int histEqualized[256];
    float hist[256];
    float sum;
    const char initHistogramFile[] = "images/output/init_histogram.txt";
    const char finalHistogramFile[] = "images/output/equalized_histogram.txt";

    computeHistogram(_inputImgData, imgRows, imgCols, hist, initHistogramFile);

    for (int i = 0; i <= 255; i++) {
        sum = 0.0f;
        for (int j = 0; j <= i; j++) {
            sum += hist[j];
        }
        histEqualized[i] = static_cast<int>(255 * sum + 0.5f);
    }

    for (int y = 0; y < imgRows; y++) {
        for (int x = 0; x < imgCols; x++) {
            _outputImgData[x + y * imgCols] =
                histEqualized[_inputImgData[x + y * imgCols]];
        }
    }

    computeHistogram(_outputImgData, imgRows, imgCols, hist, finalHistogramFile);
}

FridaBitmap::~FridaBitmap() {
    // dtor
}