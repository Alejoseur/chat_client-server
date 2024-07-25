#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 12001


int main(void) {

    char cadena[100];
    int sockfd, ret;
    struct  sockaddr_in serverAddr;
    char *tmp;
    char* ip = "127.0.0.1";

    FILE *myf = fopen("conversion_data_client.txt","a");
    time_t t;
    struct tm *tm;
    char hora[100];
    char buffer[100] = "Usando el puerto 12001\n";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("Error socket\n");
    }

    bzero(&serverAddr, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    inet_pton(AF_INET, ip, &(serverAddr.sin_addr));

    if(connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))
    <0){

        printf("Error in connect\n");
        return 1;
    }
    printf("Connection successful\n");
    
    while(!strstr(cadena, "adios") && !strstr(buffer, "adios")) {
        
        bzero(cadena, 100);
        t = time(NULL);
        tm = localtime(&t);
        strftime(hora, 100, "\n yo (%H:%M) -> ",tm);
        printf("%s",hora);
        gets(buffer);
        tmp = strcat(hora, buffer);
        fputs(tmp, myf);
        write(sockfd, buffer, strlen(buffer)+1);
       
        if(!strstr(cadena, "adios")){
            strftime(hora, 100, "\n Otro usuario (%H:%M) -> ",tm);
            read(sockfd, cadena, 100);
            tmp = strcat(hora, cadena);
            printf("%s",tmp);
            fputs(tmp, myf);

        }

    }
    printf("\n\n Conversación Finalizada \n");
    printf("\n Se genero el archivo -> conversion_data_client.txt");
    fclose(myf);

}

