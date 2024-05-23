#include "include/bmp.h"

int process_bmp(const char* inputFile, const char* outputFile) {
    
    FILE *file = fopen(inputFile, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    if (fileHeader.bfType != 0x4D42) { // 'BM' in little-endian
        fprintf(stderr, "Not a valid BMP file\n");
        fclose(file);
        return 1;
    }

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int bitCount = infoHeader.biBitCount;
    int bytesPerPixel = bitCount / 8;
    int rowSize = ((bitCount * width + 31) / 32) * 4;

    unsigned char *pixelData = (unsigned char *)malloc(rowSize * height);
    if (pixelData == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    fseek(file, fileHeader.bfOffBits, SEEK_SET);
    fread(pixelData, rowSize, height, file);

    fclose(file);

    // Use pixelData here...
    int response = convert_to_chr(pixelData, width, height, outputFile);
    if(response > 0) {
        return -1;
    }

    free(pixelData);
    return 0;
}