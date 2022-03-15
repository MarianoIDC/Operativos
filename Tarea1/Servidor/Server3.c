#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
 
void write_file(int sockfd){
//   int n;
//   FILE *fp;
//   char *filename = "recv.png";
//   char buffer[SIZE];
 
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
//   return;
//Read Picture Size
    printf("Reading Picture Size\n");
    int size;
    read(sockfd, &size, sizeof(int));

    //Read Picture Byte Array
    printf("Reading Picture Byte Array\n");
    char p_array[size];
    read(sockfd, p_array, size);

    //Convert it Back into Picture
    printf("Converting Byte Array to Picture\n");
    FILE *image;
    image = fopen("c1.jpg", "w");
    fwrite(p_array, 1, sizeof(p_array), image);
    fclose(image);
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