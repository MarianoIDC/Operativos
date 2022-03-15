#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define SIZE 1024


int size_of_image(char *imageName);
int cmp_size_of_image(char *imageName, int pixel);


 
void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "recv.txt";
  char buffer[SIZE];

  n = recv(sockfd, buffer, SIZE, 0);
 
//   fp = fopen(filename, "w");
//   while (1) {
//     n = recv(sockfd, buffer, SIZE, 0);
//     if (n <= 0){
//       break;
//       return;
//     }
//     fprintf(fp, "%s", buffer);
//     bzero(buffer, SIZE);
//   }
  return;
}
 
int main(){
  char *ip = "172.29.137.208";
  int port = 1717;
  int e;
 
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

// Funcion para conocer el tama;o de la imagen
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