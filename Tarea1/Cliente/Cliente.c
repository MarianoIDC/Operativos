#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define SIZE 1024

void send_file(int sockfd){
	FILE *fp;
	char *filename = "Archivo.txt";
  	int n;
  	char data[SIZE] = {0};
	fp = fopen(filename, "r");
		if (fp == NULL) {
			perror("No se pudo abrir el archivo");
			exit(1);
	}

  	while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, SIZE);
  	}
	fclose(fp);
  	return;
}

int main(int argc, char **argv)
{
	char *ip = "172.27.92.106";
  	int port = 8080;

	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

    
	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = port;
	servaddr.sin_addr.s_addr = inet_addr(ip);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	char buff[MAX];
	int n = 0;

	char buffer[1024] = {0};
	bzero(buffer, MAX);
	printf("--------------\n");
	printf("Ingrese la palabra que desea: \n");
	while ((buffer[n++] = getchar()) != '\n');

	/*
	if (strncmp("f", buffer, 1) == 0){
		printf("Cerrando conexión con el server... \n");
		break;
	}*/

	send(sockfd , buffer , strlen(buffer) , 0 );

	printf("Enviando la palabra... \n");
	
	bzero(buffer, MAX);
	read( sockfd , buffer, 1024);
	printf("%s\n",buffer );


	bzero(buffer, MAX);
	printf("Enviando archivo \n");

	send_file(sockfd);
	printf("Archivo enviado \n");
	//fclose(fp);
	
	//bzero(buffer, MAX);
	//read( sockfd , buffer, 1024);
	//printf("%s\n",buffer );
	
	printf("Cerrando conexión con el server... \n");
		//sleep(1);
	//}
	close(sockfd);
}