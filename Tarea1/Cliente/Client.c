#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#define BUFSIZE 7800


void send_image(FILE *fp, int sockfd, int pixels){
    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *imagename="base64.txt";
    //Image to Base64
    //system("./base64img.sh send2.png");

    //Send Pixels of image
    printf("[+]Sending Pixels\n");
    write(sockfd, &pixels, sizeof(int));

    //Send Picture Size
    printf("[+]Sending Picture Size\n");
    write(sockfd, &size, sizeof(size));

    //Send Picture as Byte Array (without need of a buffer as large as the image file)
    printf("[+]Sending Picture as Byte Array\n");
    char send_buffer[BUFSIZE]; // no link between BUFSIZE and the file size
    int nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    while(!feof(fp)) {
    write(sockfd, send_buffer, nb);
    nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    // no need to bzero
    }

}


void send_char(int sockfd, int pixels){
    


    char *filename = "base64.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 130000;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp))
        //printf("%s", buffer);
    printf(buffer);
    // close the file
    fclose(fp);
    char *imagename="base64.txt";
    //Image to Base64
    system("./base64img.sh send2.png");

    //Send Pixels of image
    printf("[+]Sending Pixels %d \n",pixels);
    write(sockfd, &pixels, sizeof(int));

    //Send Picture Size
    //printf("[+]Sending Picture Size\n");
   // write(sockfd, &size, sizeof(size));

    //Send Picture as Byte Array (without need of a buffer as large as the image file)
    printf("[+]Sending Picture as Byte Array\n");
    char send_buffer[BUFSIZE]; // no link between BUFSIZE and the file size
    int nb = fread(buffer, 1, sizeof(buffer), fp);
    while(!feof(fp)) {
    write(sockfd, buffer, nb);
    nb = fread(buffer, 1, sizeof(buffer), fp);
    // no need to bzero
    }

}

void send_file(FILE *fp, int sockfd){
    int size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Send Picture Size
    printf("[+]Sending Picture Size\n");
    write(sockfd, &size, sizeof(size));

    //Send Picture as Byte Array (without need of a buffer as large as the image file)
    printf("[+]Sending Picture as Byte Array\n");
    char send_buffer[BUFSIZE]; // no link between BUFSIZE and the file size
    int nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    while(!feof(fp)) {
    write(sockfd, send_buffer, nb);
    nb = fread(send_buffer, 1, sizeof(send_buffer), fp);
    // no need to bzero
    }

}


char* readFile(){
  char *filename = "base64.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 130000;
    char buffer[MAX_LENGTH];

    while (fgets(buffer, MAX_LENGTH, fp))
        //printf("%s", buffer);
    printf(buffer);
    // close the file
    fclose(fp);
    return buffer;
}
 
int main(){
  char *ip = "192.168.100.9";
  int port = 1717;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "base64.txt";
 
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
 
  send_image(fp, sockfd,300);
  printf("[+]File data sent successfully.\n");
 
  printf("[+]Closing the connection.\n");
  close(sockfd);
 
  return 0;
}
