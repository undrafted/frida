#include "include/FridaBitmap.h"
#include <iostream>

int main() {
    // Image parameters
    int imgWidth, imgHeight, imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgInBuffer[_512by512_IMG_SIZE];
    unsigned char imgOutBuffer[_512by512_IMG_SIZE];
    float imgHist[GRAYLEVELS_NUM];

    // File paths
    const char imgName[] = "images/image.bmp";
    // const char newImageName[] = "images/output/image_copy.bmp";
    // const char newImageName[] = "images/output/image_b&w.bmp";
    // const char newImageName[] = "images/output/image_brightenup.bmp";
    const char newImageName[] = "images/output/image_equalized.bmp";

    // Create FridaBitmap instance
    FridaBitmap *image = new FridaBitmap(
        imgName, newImageName, &imgHeight, &imgWidth, &imgBitDepth,
        imgHeader, imgColorTable, imgInBuffer, imgOutBuffer
    );

    // --- Image Operations ---
    // 1. Copy image
    // image->readImage();
    // image->copyImgData(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE);
    // image->writeImage();
    // std::cout << "Image successfully copied!\n";
    // std::cout << "Image height: " << imgHeight << "\n";
    // std::cout << "Image width: " << imgWidth << "\n";

    // 2. Binarize image
    // image->readImage();
    // image->binarizeImage(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, 64);
    // image->writeImage();
    // std::cout << "Image successfully copied and binarized!\n";

    // 3. Adjust brightness
    // int adjustment = 50;
    // image->readImage();
    // image->adjustBrightness(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, adjustment);
    // image->writeImage();
    // std::cout << "Image successfully copied and "
    //           << ((adjustment > 0) ? "brightened" : "darkened") << "!\n";

    // 4. Compute histogram
    // image->readImage();
    // image->computeHistogram(imgInBuffer, imgHeight, imgWidth, imgHist, "images/output/hist.txt");
    // std::cout << "Image histogram computed!\n";

    // 5. Histogram equalization
    image->readImage();
    image->equalizeHistogram(imgInBuffer, imgOutBuffer, imgHeight, imgWidth);
    image->writeImage();
    std::cout << "Image histogram equalized and written!\n";

    delete image;
    return 0;
}