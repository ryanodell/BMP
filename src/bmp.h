#ifndef BMP_H
#define BMP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Bitmap File Header
#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;      // Magic number for file
    uint32_t bfSize;      // Size of file
    uint16_t bfReserved1; // Reserved
    uint16_t bfReserved2; // Reserved
    uint32_t bfOffBits;   // Offset to bitmap data
} BITMAPFILEHEADER;

// Bitmap Info Header
typedef struct {
    uint32_t biSize;          // Size of info header
    int32_t  biWidth;         // Width of image
    int32_t  biHeight;        // Height of image
    uint16_t biPlanes;        // Number of color planes
    uint16_t biBitCount;      // Number of bits per pixel
    uint32_t biCompression;   // Type of compression to use
    uint32_t biSizeImage;     // Size of image data
    int32_t  biXPelsPerMeter; // X pixels per meter
    int32_t  biYPelsPerMeter; // Y pixels per meter
    uint32_t biClrUsed;       // Number of colors used
    uint32_t biClrImportant;  // Number of important colors
} BITMAPINFOHEADER;
#pragma pack(pop)

int process_bmp(const char* inputFile, const char* outputFile);

#endif