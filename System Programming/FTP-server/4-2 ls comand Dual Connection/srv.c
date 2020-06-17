//////////////////////////////////////////////////////////////////////
// File Name    : srv.c                                             //
// Date         : 2020/06/18                                        //
// Os           : Ubuntu 18.04.4 LTS 64bits                         //
// Author       : Cho So Young                                      //
// Student ID   : 2017204050                                        //
// ---------------------------------------------------------------- //
// Title : System Programming Assiginment #4-2 (server)             //
// Description : Implementation of Split Connection                 //
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pwd.h>

//////////////////////////////////////////////////////////////////////
// Program of implemented split connection                          //
// ================================================================ //
// Input : port number                                              //
// Output : display port info, numerical response message           //
// Purpose : server implementing split connection (control & data)  //
//////////////////////////////////////////////////////////////////////


#define MAX_BUF 30
#define TRUE 1
#define FALSE 0

//define functions
char* convert_str_to_addr(char *str, unsigned int *port);
char *client_info(struct sockaddr_in *client);
void initialize(char buff[], int length);

// main function
int main(int argc, char **argv){ 
    char *host_ip;
    char temp[25];
    int listenfd, connfd;
    struct sockaddr_in server, client;
    int cli_len;
    unsigned int port_num;
    char buff[MAX_BUF];
    pid_t childpid;

    ////////////// SERVER Implementation //////////////
    // 1. create socket
    if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server)); // initialize server memory
    server.sin_family           = AF_INET;
    server.sin_addr.s_addr      = htonl(INADDR_ANY); // server IP address, find automatically
    server.sin_port             = htons(atoi(argv[1])); // server port number

    // 2. bind
    if(bind(listenfd, (struct sockaddr*)&server, sizeof(server)) == -1){;  // associate and address with a socket. sd is server socket descriptor
        perror("bind"); // exception handling
        exit(1);
    }

    // 3. listen
    if(listen(listenfd, 5) == -1){ // willing to accept connect request
        perror("listen"); // exception handling
        exit(1);
    }

    // wait for client. blocked until request connect
    while(TRUE){
        initialize(buff, MAX_BUF); // initialize buffer
        cli_len = sizeof(client); // length of socket address

        // 4. accept and display client info
        connfd = accept(listenfd, (struct sockaddr *)&client, &cli_len); // accept a connect request from client
        host_ip = client_info(&client); // display client ip and port

        // 5. read
        read(connfd, buff, MAX_BUF); // read SPLIT command from client
        printf("server reads command %s \n", buff);

        // 6. FORK
        if(!strcmp(buff, "SPLIT")){
            if((childpid = fork()) == 0){ // child client process (data conncection)
            
            }
        }
        else if(!strcmp(buff, "UNKNOWN")){
            printf("UNKNOWN");
        }
        getchar();

    // my code
    // make control connection

    }


    //host_ip = convert_str_to_addr(temp, (unsigned int *)&port_num);
    // my code
    // make data connection
    // your own code
}

char* convert_str_to_addr(char *str, unsigned int *port){
    // change IP address and port num in PORT command received from client
    char *addr;

    
    // my converting algorithm
    return addr;
}

////////////// function to print client information about IP address and Port number //////////////
char *client_info(struct sockaddr_in *client){
    char *client_ip = inet_ntoa(client->sin_addr);
    int client_port = ntohs(client->sin_port);

    printf("** Client is trying to connect **\n");
    printf("- IP :  %s\n", client_ip);
    printf("- Port :    %d\n", client_port);
    return client_ip;
}

////////////// function to initialize buffer //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
} 