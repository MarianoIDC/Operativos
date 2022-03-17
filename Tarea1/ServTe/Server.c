#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "stb_image/stb_image.h"
#define SIZE 1024
#define BUFSIZE 7800


int size_of_image(char *imageName);
int cmp_size_of_image(char *imageName, int pixel);


void write_file(int sockfd){

    //Read Pixels of picture
    int pixels;
    read(sockfd, &pixels, sizeof(int));
    printf("[+]Pixels received->%d \n",pixels);
    //Read Picture Size
    printf("[+]Reading Picture Size\n");
    int size;
    read(sockfd, &size, sizeof(int));

    //Read Picture Byte Array and Copy in file
    printf("[+]Reading Picture Byte Array\n");
    char p_array[BUFSIZE];
    FILE *image = fopen("server.txt", "w");
    int nb = read(sockfd, p_array, BUFSIZE);
    while (nb > 0) {
        fwrite(p_array, 1, nb, image);
        nb = read(sockfd, p_array, BUFSIZE);
    }
    fclose(image);

    
    //system("./decodebase64.sh decoded.png");
    //int compare= cmp_size_of_image("decoded.png",pixels);
    //printf("[+]Exist %d px after the pixel %d px\n", compare, pixels);
}

 
int main(){
  char *ip = "192.168.100.9";
  int port = 1717;
  int e;
  //int compare= cmp_size_of_image("c1.png",300);
  //printf("[+]Exist %d px after the pixel %d px\n", compare, 300);
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");
 
  if(listen(sockfd, 10) == 0){
 printf("[+]Listening....\n");
 }else{
 perror("[-]Error in listening");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  printf("[+]Data written in the file successfully.\n");
 
  return 0;
}


int size_of_image(char *imageName){
    int width, height, channels;
    unsigned char *img = stbi_load(imageName, &width, &height, &channels, 0);
    if(img == NULL) {
        printf("[-]Error in loading the image\n");
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


// How to RUN
// gcc -std=c17 -Wall Server.c -o Server -lm
// ./Server
