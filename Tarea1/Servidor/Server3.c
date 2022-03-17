#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
#define BUFSIZE 1080

void write_file(int sockfd){

    //Read Picture Size
    printf("[+]Reading Picture Size\n");
    int size;
    read(sockfd, &size, sizeof(int));

    //Read Picture Byte Array and Copy in file
    printf("[+]Reading Picture Byte Array\n");
    char p_array[BUFSIZE];
    FILE *image = fopen("c1.png", "w");
    int nb = read(sockfd, p_array, BUFSIZE);
    while (nb > 0) {
        fwrite(p_array, 1, nb, image);
        nb = read(sockfd, p_array, BUFSIZE);
    }
    fclose(image);
}
 
int main(){
  char *ip = "172.17.226.245";
  int port = 2525;
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
