
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


#define BUF_SIZE 256


//gcc Client.c -o Client
// ./Client 192.168.100.9 1717 mario.png 1000


int client(char* ip, int PORT, const char* filename, int pixels)
{
    
    /* Create file where data will be stored */
   

    /* Create a socket first */
    int sockfd = 0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("[-]Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); // port
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("[-]Error : Connect Failed \n");
        return 1;
    }

   
        /* Open the file that we wish to transfer */
        FILE *fp = fopen(filename,"rb");
        if(fp==NULL)
        {
            printf("[-]File open error");
            return 1;
        }
        /*
        //Send Filename of image
        printf("[+]Sending Filename %d \n",filename);
        //write(sockfd, &pixels, sizeof(int));
        write(sockfd, &filename, sizeof(filename));
        */
        //Send Pixels of image
        printf("[+]Sending Pixels %d \n",pixels);
        //write(sockfd, &pixels, sizeof(int));
        write(sockfd, &pixels, sizeof(int));
        //Send Pixels of image
        //printf("[+]Sending extension file %d \n",extension);
        //write(sockfd, &extension, sizeof(int));
        /* Read data from file and send it */
        for (;;)
        {
            /* First read file in chunks of BUF_SIZE bytes */
            unsigned char buff[BUF_SIZE]={0};
            int nread = fread(buff,1,BUF_SIZE,fp);
            //printf("Bytes read %d \n", nread);

            /* If read was success, send data. */
            if(nread > 0)
            {
                //printf("Sending \n");
                write(sockfd, buff, nread);
            }

            /*
             * There is something tricky going on with read ..
             * Either there was error, or we reached end of file.
             */
            if (nread < BUF_SIZE)
            {
                if (feof(fp))
                    printf("[+]File send it!\n");
                if (ferror(fp))
                    printf("[-]Error reading\n");
                break;
                
            }
        }
        close(sockfd);
        sleep(1);
   
    return 0;
}
int detect_format(char* extension){
    if(strcmp(extension, "PNG") == 0){
        return 0;
    }
    else if(strcmp(extension, "JPG") == 0){
        return 1;
    }
    else if(strcmp(extension, "GIF") == 0){
        return 2;
    }
    else if(strcmp(extension, "JPEJ") == 0){
        return 3;
    }
}

int main(int argc, char** argv)
{
    if (argc == 5)
    {
        char *ip = argv[1];
        char *b= argv[2];
        const char* filename = argv[3];
        char *a = argv[4];
        //char *format = argv[3];
        int pixels = atoi(a);
        int PORT = atoi(b);
        //int extension=detect_format(format);
        //printf("Extension %d",extension);
        //return client(filename, pixels, extension);
        return client(ip, PORT, filename, pixels);

    }
    else
    {
        printf("[-]Invalid number of argument, usage is %s [IPSERVER] [PORT] [FILENAME] [PIXELS] \n",argv[0]);
    }
    return 1; // Something went wrong
}