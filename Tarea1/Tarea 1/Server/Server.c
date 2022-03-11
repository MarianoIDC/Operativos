#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define MAX_LARGO_PALABRA 50
#define SIZE 1024

void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "recv.txt";
  char buffer[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  fclose(fp);
  return;
}
void contar(char palabra[30]){

	FILE *Fd;
    char texto[80];
    int i,tmp1,tmp2,konta=0;

    Fd=fopen("recv.txt","r");
    if (Fd==NULL)
        printf("Error abriendo el fichero");

    while (feof(Fd)==0)
    {
        fgets(texto,80,Fd);
        for(i=0;i<strlen(texto);i++)
        {
            if (palabra[0]==texto[i])
            {
                tmp1=0;
                tmp2=i;
                while ((palabra[tmp1]==texto[tmp2])&&(tmp2<strlen(texto))&&(tmp1!=strlen(palabra)))
                {
                    tmp1++;
                    tmp2++;
                    if (tmp1==strlen(palabra))
                        konta++;
                }
            }
        }
    }
	printf("%s\n",palabra);
    printf("La palabra se repite en el texto %d veces \n",konta);

    //getchar();
	fclose(Fd);
}


// Driver function
int main(int argc, char **argv)
{
	char *ip = "192.168.0.22";
    int port = 8080;
    // Variables de la funcion de leer palabras
    int n;
    char **palabras;
    int *cuentas;
    FILE *f;
    char palabra_actual[MAX_LARGO_PALABRA];
    int i;


    //Variables del server
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
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

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");

    //for(;;){
    char buffer[1024] = {0}; 
    char *hello = "Ok, recibido";
    
    //Se lee la palabra enviada por el cliente
    read( connfd , buffer, sizeof(buffer));
    /*
    if(strncmp("f",buffer,1) == 0){
        break;
    }*/
    printf("-----------------\n");
    char palabra[30] = {0};
    i = 0;
    // Se pasa lo que viene en el buffer a la palabra
    while(sizeof(buffer))
    {
        if(buffer[i] != '\n'){
            palabra[i] = buffer[i];
        }
        else{
            break;
        }
        i++;  
    }
    // Se envìa un mensaje de confirmaciòn
    send(connfd , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");

    bzero(buffer, sizeof(buffer));
    printf("Recibiendo archivo\n");
    // Se recibe el archivo enviado por el cliente
    write_file(connfd);
    printf("Archivo recibido\n");

    //bzero(buffer, sizeof(buffer));
    //send(connfd , hello , strlen(hello) , 0);
 
 
    // Se inicia algoritmo para contar las palabras repetidas en el archivo
    contar(palabra);
    
    //Se cierra la conexiòn con el cliente
    printf("Cerrando conexion con el cliente\n");
    //}
	close(sockfd);
}
