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

int size_of_image(char *imageName);
int cmp_size_of_image(char *imageName, int pixel);

//gcc -std=c17 -Wall Server.c -o Server -lm
//gcc Server.c -o Server
// ./Server server z.png
//gcc Client.c -o Client
// ./Client client mario.png
// For server


#define PORT 1717
#define BUF_SIZE 256


int server()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    char* filename;
    printf("[+]Server socket created successfully.\n");

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

    remove("image.png");
    remove("image.jpg");
    remove("image.jpeg");
    remove("image.gif");
    for (;;)
        {
        
        int connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
        //remove(filename);//Eliminar archivo
        //FILE *fp = fopen(filename, "ab");
        //Read Pixels of picture
        int pixels;
        read(connfd, &pixels, sizeof(int));

        int extension;
        read(connfd, &extension, sizeof(int));

        if(extension== 0){
            filename="image.png";
        }
        else if(extension == 1){
            filename="image.jpg";
        }
        else if(extension == 2){
            filename="image.gif";
        }
        else if(extension == 3){
            filename="image.jpej";
        }
        remove(filename);//Eliminar archivo
        printf(filename);
        
        //Eliminar archivo 
        //remove(filename);//Eliminar archivo
        /* Create file where data will be stored */
        FILE *fp = fopen(filename, "ab");
        if(NULL == fp)
        {
            printf("[-]Error opening file.");
            return 1;
        }


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
        int compare= cmp_size_of_image(filename,pixels);
        printf("[+]Exist %d px after the pixel %d px\n", compare, pixels);
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

        //const char* filename = argv[1];
        //const char* filename = "mario.png";
        return server();
        
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