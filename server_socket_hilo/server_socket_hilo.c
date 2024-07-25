#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>


#define PORT 12001


int main(){
  
	char cadena[100];
    int listen_fd, comm_fd, ret;
    struct  sockaddr_in serverAddr;
    char *tmp;

    FILE *myf = fopen("conversion_data_server.txt","a");
    time_t t;
    struct tm *tm;
    char hora[100];
    char buffer[100] = "Usando el puerto 12001\n";

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serverAddr, sizeof(serverAddr));

	printf("[+]Server Socket is created.\n");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

	ret = bind(listen_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", PORT);

	if(listen(listen_fd, 10) == 0){
		

	}else{
		printf("[-]Error in binding.\n");
	}
	printf("\n\n------Starting chat------\n\n");
	fputs("\n\n------Starting chat------\n\n", myf);

	comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

	

	while(!strstr(cadena, "adios") && !strstr(buffer, "adios")){

		bzero(cadena, 100);
        t = time(NULL);
        tm = localtime(&t);
        strftime(hora, 100, "\n Otro usuario (%H:%M) -> ",tm);
        read(comm_fd, cadena, 100);
        tmp = strcat(hora, cadena);
        printf("%s",tmp);
        fputs(tmp, myf);
        if(!strstr(cadena, "adios")){
            strftime(hora, 100, "\n yo (%H:%M) -> ",tm);
            printf("%s",hora);
            gets(buffer);
            tmp = strcat(hora, buffer);
            write(comm_fd,buffer, strlen(buffer)+1);
            fputs(tmp, myf);

        }


    }
	printf("\n\n Conversación Finalizada \n");
    printf("\n Se genero el archivo -> conversion_data_server.txt");
    fclose(myf);

	return 0;
}

