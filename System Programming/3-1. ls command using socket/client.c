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

//////////////////////////////////////////////////////////////////////
// Program of implementing client for ls command using socket       //
// ================================================================ //
// Input : IP address and port number                               //
// Output : print command result received from server               //
// Purpose : client using socket(), connect() etc.                  //
//////////////////////////////////////////////////////////////////////

#define MAX_BUFF 256
#define RCV_BUFF 256

int process_result(int sd, char *cmd_buff, char *rcv_buff, int cmd_len);
void initialize(char buff[], int length);

void main(int argc, char **argv){
    char buff[MAX_BUFF], cmd_buff[MAX_BUFF], rcv_buff[RCV_BUFF];
    int n, sd;
    struct sockaddr_in server;

    // exception handling
    if(argc != 3){
        printf("Client takes two arguments only.\n"); // client takes only IP address and Port number
        return;
    }

    ////////////// CLIENT Implementation //////////////
    // 1. create socket
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // IPv4 Internet Domain, connection-oriented
        perror("socket");
        exit(1);
    }

    memset((char*)&server, '\0', sizeof(server));   // initialize server memory
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);  // server IP address client willing to connect
    server.sin_port = htons(atoi(argv[2])); // server port number client willing to connect

    // 2. connect
    if(connect(sd, (struct sockaddr*)&server, sizeof(server)) == -1){ // client requests a connection to server
        printf("Invalid Port number.\n");
        return;
    }

    /* open socket and connect to server */

    while(1){
        printf("\nInput command : ");
        fgets(cmd_buff, MAX_BUFF, stdin); // client enters command
        cmd_buff[strlen(cmd_buff)-1] = '\0';
        int cmd_len = strlen(cmd_buff);

        process_result(sd, cmd_buff, rcv_buff, cmd_len); // call process result funtion
    }
    close(sd);
}

////////////// function to split buffer with blank space //////////////
int split(char buff[]){
    int count = 0;
    char *arr[MAX_BUFF];
    char copy[MAX_BUFF];
    strcpy(copy, buff);
    char *ptr = strtok(copy, " "); 

    while(ptr != NULL){ // split buff
        arr[count] = ptr; // save token in arr
        ptr = strtok(NULL, " ");
        count++; // count number of tokens in buff
    }
    return count;
}


////////////// function to check whether buff starts with specific letters //////////////
int startswith(char buff[], char *start){
    int length = strlen(start);
    
    for(int i = 0; i < length; i++){
        if(buff[i] != start[i])
            return 0; // return 0 if buff does not start with buff
    }
    if(buff[2] == '\0' || buff[2] == ' ') // third letter null or blank space
        return 1;

    return 0;
}

////////////// function to process result //////////////
int process_result(int sd, char *cmd_buff, char *rcv_buff, int cmd_len){
    int count = split(cmd_buff);

    if(startswith(cmd_buff, "ls") && (count == 1 || count == 2)){ // command starts with ls and is only ls or ls with one argument
        send(sd, cmd_buff, cmd_len, 0); // send command to server
        initialize(rcv_buff, MAX_BUFF); // initialize buffer

        read(sd, rcv_buff, RCV_BUFF); // receive (read) from server
        printf("\n%s\n", rcv_buff); // print received result
    }
    else if(!strcmp(cmd_buff, "quit")){ // if user input command is quit
        send(sd, cmd_buff, cmd_len, 0); // send command quit to server
        read(sd, rcv_buff, RCV_BUFF); // receive (read) from server
        exit(1); // exit
    }
    else{
        printf("Unsupported Command %s\n", cmd_buff);
        printf("Please Re-enter ...\n");
    }
    initialize(cmd_buff, MAX_BUFF); // initialize buffer
    return 0;
}

////////////// function to initialize //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
}
