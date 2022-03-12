//References:
//https://github.com/nothings/stb
//https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/


#include <stdio.h>
#include <stdlib.h> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

void load_file(char *imageName);
int size_of_image(char *imageName);
int main(void) {
    char *imageName="sunset_940_530.jpg";
    load_file(imageName);
    int size= size_of_image(imageName);
}
//gcc -std=c17 -Wall code.c -o code -lm
//./code
//char *s  = "geeksquiz";
void load_file(char *imageName){
    int width, height, channels;
    unsigned char *img = stbi_load(imageName, &width, &height, &channels, 0);
    if(img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
}

int size_of_image(char *imageName){
    int width, height, channels;
    unsigned char *img = stbi_load(imageName, &width, &height, &channels, 0);
    if(img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    int size= width*height;
    printf("The size of image is: %d px\n", size);
    return size;
}