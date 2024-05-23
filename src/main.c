#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/bmp.h"

void print_usage(const char *program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -i <input_file>  Specify input file\n");
    printf("  -o <output_file> Specify output file\n");
    printf("  -h               Display this help message\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    char *input_file = NULL;
    char *output_file = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                input_file = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "Error: -i option requires a value\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "Error: -o option requires a value\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    if (input_file) {
        printf("Input file: %s\n", input_file);
    }
    if (output_file) {
        printf("Output file: %s\n", output_file);
    }
    int result = process_bmp(input_file, output_file);
    printf("Finished");
    getchar();
    return 0;
}
