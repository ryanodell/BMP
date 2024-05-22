#include "include/chr.h"

int convert_to_chr(unsigned char *bmpData, int width, int heigh, const char* outputFile) {
    FILE* file = fopen(outputFile, "wb");
    if(!file) {
        perror("Failed to open/create output file");
        return -1;
    }
    //Test code:
    unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t bytesWritten = fwrite(data, sizeof(unsigned char), sizeof(data), file);
    if (bytesWritten != sizeof(data)) {
        perror("Failed to write all bytes to file");
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}



/* KEEP THIS FOR REFERENCE
#include <stdio.h>
#include <stdlib.h>

void convertToCHR(unsigned char *bmpData, int width, int height, const char *outputFile) {
    FILE *file = fopen(outputFile, "wb");
    if (!file) {
        perror("Failed to open output file");
        return;
    }

    // Ensure height is a multiple of 8 for tile conversion
    for (int y = 0; y < height; y += 8) {
        for (int x = 0; x < width; x += 8) {
            // Process each 8x8 tile
            for (int row = 0; row < 8; ++row) {
                unsigned char plane0 = 0;
                unsigned char plane1 = 0;
                for (int col = 0; col < 8; ++col) {
                    int pixelIndex = (y + row) * width + (x + col);
                    unsigned char pixel = bmpData[pixelIndex];

                    // Map pixel to NES color (0-3)
                    unsigned char color = pixel % 4; // Assuming a simple grayscale mapping for illustration

                    plane0 |= ((color & 1) << (7 - col));
                    plane1 |= (((color >> 1) & 1) << (7 - col));
                }
                fwrite(&plane0, 1, 1, file);
                fwrite(&plane1, 1, 1, file);
            }
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input.bmp> <output.chr>\n", argv[0]);
        return 1;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];

    FILE *bmpFile = fopen(inputFile, "rb");
    if (!bmpFile) {
        perror("Failed to open BMP file");
        return 1;
    }

    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;

    fread(&bmpHeader, sizeof(BMPHeader), 1, bmpFile);
    fread(&bmpInfoHeader, sizeof(BMPInfoHeader), 1, bmpFile);

    if (bmpHeader.bfType != 0x4D42) {
        fprintf(stderr, "Not a valid BMP file\n");
        fclose(bmpFile);
        return 1;
    }

    int width = bmpInfoHeader.biWidth;
    int height = bmpInfoHeader.biHeight;

    fseek(bmpFile, bmpHeader.bfOffBits, SEEK_SET);
    unsigned char *bmpData = (unsigned char *)malloc(width * height);
    if (!bmpData) {
        perror("Failed to allocate memory for BMP data");
        fclose(bmpFile);
        return 1;
    }

    fread(bmpData, 1, width * height, bmpFile);
    fclose(bmpFile);

    convertToCHR(bmpData, width, height, outputFile);

    free(bmpData);
    printf("Conversion to CHR format complete.\n");

    return 0;
}

*/