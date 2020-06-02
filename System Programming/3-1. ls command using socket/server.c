//////////////////////////////////////////////////////////////////////
// Os           : Ubuntu 18.04.4 LTS 64bits                         //
// Author       : Cho So Young                                      //
// ---------------------------------------------------------------- //
// Title : ls implementaion                                         //
// Description : Implementation of ls command using socket()        //
//////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

//////////////////////////////////////////////////////////////////////
// Program of implementing server for ls command using socket       //
// ================================================================ //
// Input : port number                                              //
// Output : return result for client request                        //
// Purpose : server using socket(), bind(), listen(), receive(), etc//
//////////////////////////////////////////////////////////////////////

#define MAX_BUFF 256
#define SEND_BUFF 256
#define BACKLOG 1
#define ERROR_OCCUR "-1"
#define TRUE 1

// define functions
int startswith(char buff[], char *start);
int cmd_process(char buff[], char result_buff[], int cd, char *client_ip);
char *client_info(struct sockaddr_in *client);
void initialize(char buff[], int length);

// main function
int main (int argc, char **argv){
    char buff[MAX_BUFF], result_buff[SEND_BUFF];
    struct sockaddr_in server, client; // sockect address structure for server and client
    int sd, cd, clilen = sizeof(client);
    int n;

    // exception handling when server takes more than one argument.
    if(argc != 2){
        printf("Server takes one argument only.\n"); // server takes port number argument
        return 0;
    }

    ////////////// SERVER Implementation //////////////
    // 1. create socket
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // IPv4 Internet Domain, connection-oriented
        perror("socket");
        exit(1);
    }

    memset((char *)&server, '\0', sizeof(server)); // initialize server memory
    server.sin_family       = AF_INET;
    server.sin_addr.s_addr  = htonl(INADDR_ANY); // server IP address, find automatically
    server.sin_port         = htons(atoi(argv[1])); // server port number

    // 2. bind
    if(bind(sd, (struct sockaddr*)&server, sizeof(server)) == -1){ // associate and address with a socket. sd is server socket descriptor
        perror("bind"); // exception handling
        exit(1);
    }

    // 3. listen
    if(listen(sd, BACKLOG) == -1){ // willing to accept connect request
        perror("listen"); // exception handling
        exit(1);
    }

    // wait for client. blocked until request connect
    while(TRUE){ 
        printf("\nServer waiting for Client ...\n");

        // 4. accept
        cd = accept(sd, (struct sockaddr*)&client, &clilen); // accept a connect request from client
        printf("Connction accepted with new process.\n");

        char *client_ip = client_info(&client); // display client ip and port

        while(TRUE){
            initialize(buff, MAX_BUFF); // initialize buffer
            // 5. read
            read(cd, buff, MAX_BUFF); // receive data from client descriptor cd in buff
            if(cmd_process(buff, result_buff, cd, client_ip) == -1) // exception handling
                break;
        }
    }

    // 6. close
    close(cd); // disable I/O on client and server socket
    close(sd);
}

////////////// function to check whether buff starts with specific letters //////////////
int startswith(char buff[], char *start){
    int length = strlen(start);
    
    for(int i = 0; i < length; i++){
        if(buff[i] != start[i])
            return 0; // return 0 if buff does not start with buff
    }
    return 1; // return 1 if buff starts with start
}

////////////// function to read buff, process command and save result //////////////
int cmd_process(char buff[], char result_buff[], int cd, char *client_ip){
    DIR *dp; 
    struct dirent *dirp;
    char pathname[128];

    char getStr[MAX_BUFF];
    char *arr[MAX_BUFF];
    char *ptr = strtok(buff, " "); 

    int count = 0;

    while(ptr != NULL){ // split buff with blank space 
        arr[count] = ptr;
        ptr = strtok(NULL, " "); 
        count++; // count number of tokens in buff
    }

    if(startswith(buff, "ls") && (count == 1 || count == 2)){    // if buffer starts with ls and is only ls or ls with one argument
        printf("%s client : %s\n", client_ip, buff);

        if(count == 1){ // only one argument : ls
            strcpy(pathname, "."); // set pathname as current directory
        }
        else if (count == 2){ // two arguments : ls with pathname
            strcpy(pathname, arr[1]); // set pathname as passed argument
        }

        if((dp = opendir(pathname)) != NULL){ // use opendir() and open pathnmae
            initialize(result_buff, MAX_BUFF); // initialize result_buff
            while(dirp = readdir(dp)){ // use readdir() to read file names
                if (dirp -> d_ino != 0){
                    strcat(result_buff, dirp->d_name); // save in result_buff
                    strcat(result_buff, "\n");
                }
            }
            write(cd, result_buff, strlen(result_buff)-1); // send processed result to client socket
            
            closedir(dp); // close directory
            return 0;
        }
        else{ // exception handling when pathname can not be opened
            write(cd, "can`t open", strlen("can`t open"));
        }

    }
    else if(!strcmp(buff, "quit")){ // if client sended 'quit' command
        printf("%s client quit..\n", client_ip);
        write(cd, "client quit", strlen("client quit")); // send message to client socket
    }

    return 0;
}

////////////// function to print client information about IP address and Port number //////////////
char *client_info(struct sockaddr_in *client){
    char *client_ip = inet_ntoa(client->sin_addr);
    int client_port = ntohs(client->sin_port);

    printf("\n========== Client Info ==========\n");
    printf("client IP : %s\n\n", client_ip);
    printf("client port : %d\n", client_port);
    printf("=================================\n\n");
    return client_ip;
}

////////////// function to initialize //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
}
