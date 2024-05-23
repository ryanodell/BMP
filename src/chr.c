#include "include/chr.h"

int convert_to_chr(unsigned char *bmpData, int width, int height, const char* outputFile) {
    FILE* file = fopen(outputFile, "wb");
    if(!file) {
        perror("Failed to open/create output file");
        return -1;
    }
    for(int y = 0; y < height; y += 8) {
        for(int x = 0; x < width; x += 8) {
            //Process chunk of 8x8 pixels
            unsigned char plane0 = 0;
            unsigned char plane1 = 0;
            for(int row = 0; row < 8; ++row) {
                for(int col = 0; col < 8; ++col) {
                    int pixelIndex = (y + row) * width + (x + col);
                    unsigned char pixel = bmpData[pixelIndex];
                    unsigned char color = pixel % 4;
                    plane0 |= ((color & 1) << (7 - col));
                    plane1 |= (((color >> 1) & 1) << (7 - col));
                }
                fwrite(&plane0, 1, 1, file);
                fwrite(&plane1, 1, 1, file);
            }            
        }
    }
    fclose(file);
    return 0;
}