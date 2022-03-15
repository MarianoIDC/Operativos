#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#define BUFSIZE 1080
 
void send_file(FILE *fp, int sockfd){
    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Send Picture Size
    printf("Sending Picture Size\n");
    write(sockfd, &size, sizeof(size));

    // printf("Sending Picture as Byte Array\n");
    //     char send_buffer[size];
    //     while(!feof(fp)) {
    //         fread(send_buffer, 1, sizeof(send_buffer), fp);
    //         write(sockfd, send_buffer, sizeof(send_buffer));
    //         bzero(send_buffer, sizeof(send_buffer));
    //     }

    //Send Picture as Byte Array (without need of a buffer as large as the image file)
    printf("Sending Picture as Byte Array\n");
    char send_buffer[BUFSIZE]; // no link between BUFSIZE and the file size
    int nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    while(!feof(fp)) {
    write(sockfd, send_buffer, nb);
    nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    // no need to bzero
    }

}
 
int main(){
  char *ip = "172.29.137.208";
  int port = 1717;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "send2.png";
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");
 
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }
 
  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");
 
  printf("[+]Closing the connection.\n");
  close(sockfd);
 
  return 0;
}