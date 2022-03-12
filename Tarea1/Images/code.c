//References:
//https://github.com/nothings/stb
//https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/

// How to RUN
// gcc -std=c17 -Wall code.c -o code -lm
// ./code

#include <stdio.h>
#include <stdlib.h> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

void load_file(char *imageName);
int size_of_image(char *imageName);
int cmp_size_of_image(char *imageName, int pixel);


int main(void) {
    char *imageName="sunset_940_530.jpg";
    load_file(imageName);
    int size= size_of_image(imageName);
    printf("The size of image is: %d px\n", size);
    int pixel=500;
    int compare= cmp_size_of_image(imageName, pixel);
    printf("Exist %d px after the pixel %d px\n", compare, pixel);
}

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
    
    return size;
}

// Funcion recibir las imagenes de manera secuencial y un parametro (valor de pixel),
//este modulo retornara la cantidad de pixeles en la imagen que son mayores a al parametro
//recibido.
int cmp_size_of_image(char *imageName, int pixel){
    int size= size_of_image(imageName);
    if(pixel>size){
        return 0;
    }
    return size-pixel;
}