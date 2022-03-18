#define STB_IMAGE_IMPLEMENTATION
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "stb_image/stb_image.h"
#define LSIZ 128 
#define RSIZ 10 

int size_of_image(char *imageName);
int cmp_size_of_image(char *imageName, int pixel);

//gcc -std=c17 -Wall Server.c -o Server -lm
//gcc Server.c -o Server
// ./Server 1717 z.png
//gcc Client.c -o Client
// ./Client client mario.png
// For server


#define BUF_SIZE 256

//#define PORT 1717

//int server(int PORT, const char * filename)
//int server(const char * filename)
int server(int PORT, const char * filename)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("[+]Server socket created successfully.\n");
    FILE *LOG;
        LOG = fopen("log.txt", "a");
        fprintf(LOG, "[+]Server socket created successfully.\n");
        fclose(LOG);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

    if(listen(listenfd, 10) == -1)
    {
        printf("[-]Failed to listen\n");
        return -1;
    }

    //Eliminar archivo 
    remove(filename);//Eliminar archivo
    /* Create file where data will be stored */
    FILE *fp = fopen(filename, "ab");
    if(NULL == fp)
    {
        printf("[-]Error opening file.");
        return 1;
    }
    for (;;)
        {
        int connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
        //remove(filename);//Eliminar archivo
        //FILE *fp = fopen(filename, "ab");
        //Read Pixels of picture
        int pixels;
        read(connfd, &pixels, sizeof(int));
        //printf("[+]Pixels received->%d \n",pixels);
        /* Receive data in chunks of BUF_SIZE bytes */
        int bytesReceived = 0;
        char buff[BUF_SIZE];
        memset(buff, '0', sizeof(buff));
        while((bytesReceived = read(connfd, buff, BUF_SIZE)) > 0)
        {
            //printf("Bytes received %d\n",bytesReceived);
            fwrite(buff, 1,bytesReceived,fp);
        }
        close(connfd);
        
        LOG = fopen("log.txt", "a");
        fprintf(LOG, "[+]Image Received from Client!\n");
        fclose(LOG);
        int compare= cmp_size_of_image(filename,pixels);
       
        
        LOG = fopen("log.txt", "a");
        fprintf(LOG, "[+]Exist %d px after the pixel %d px\n", compare, pixels);
        fprintf(LOG, "[-]Close Connection\n");
        fclose(LOG);
        sleep(1);

        /*if(bytesReceived < 0)
        {
            printf("\n Read Error \n");
        }*/
    }

    return 0;
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
    char line[RSIZ][LSIZ];
	char* fname="conf.ini";
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    char* temp=line[1];
    int PORT = atoi(temp);
    //printf(" %d\n", PORT);
    char* PATH=line[3]; 
        //char *a = argv[1];
        //int PORT = atoi(a);
        //const char* filename = argv[2];
        const char* filename = "image.png";
        //return server(filename);
        FILE *LOG;
        LOG = fopen("log.txt", "a");
        fprintf(LOG, "[+]Server Started in Port %d \n", PORT);
        fclose(LOG);
        return server(PORT, filename);
    }
    else
    {
        printf("Invalid number of argument, usage is %s \n",argv[0]);
    }
    return 1; // Something went wrong
}

int size_of_image(char *imageName){
    int width, height, channels;
    unsigned char *img = stbi_load(imageName, &width, &height, &channels, 0);
    /*if(img == NULL) {
        printf("[-]Error in loading the image\n");
        exit(1);
    }*/
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