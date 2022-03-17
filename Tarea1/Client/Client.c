
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

#define PORT 1717
#define BUF_SIZE 256

int client(const char* filename)
{
    char *ip = "127.0.0.1";
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
        printf("[-] Error : Connect Failed \n");
        return 1;
    }

    //for (;;)
    //{
        //int connfd = accept(sockfd, (struct sockaddr*)NULL ,NULL);

        /* Open the file that we wish to transfer */
        FILE *fp = fopen(filename,"rb");
        if(fp==NULL)
        {
            printf("[-]File open error");
            return 1;
        }

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
    //}

    return 0;
}


int main(int argc, char** argv)
{
    if (argc == 3)
    {
        const char* mode = argv[1];
        const char* filename = argv[2];
        //const char* filename = "mario.png";
        if (strcmp(mode, "client") == 0)
            return client(filename);

        else
            printf("Invalid mode %s - should be 'client' or 'server'\n",mode);
    }
    else
    {
        printf("Invalid number of argument, usage is %s [MODE] [FILENAME]\n",argv[0]);
    }
    return 1; // Something went wrong
}