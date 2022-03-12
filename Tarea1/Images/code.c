//References:
//https://github.com/nothings/stb
//https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/


#include <stdio.h>
#include <stdlib.h> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"


int main(void) {
    int width, height, channels;
    unsigned char *img = stbi_load("sunset_940_530.jpg", &width, &height, &channels, 0);
    if(img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
}
//gcc -std=c17 -Wall code.c -o code -lm
//./code