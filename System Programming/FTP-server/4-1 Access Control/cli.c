//////////////////////////////////////////////////////////////////////
// File Name    : cli.c                                             //
// Date         : 2020/06/11                                        //
// Os           : Ubuntu 18.04.4 LTS 64bits                         //
// Author       : Cho So Young                                      //
// Student ID   : 2017204050                                        //
// ---------------------------------------------------------------- //
// Title : System Programming Assiginment #4-1 (client)             //
// Description : Implementation of Access Control and User Authentication//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>

//////////////////////////////////////////////////////////////////////
// Program of implementing access control and user authentication   //
// ================================================================ //
// Input : IP address and port number                               //
// Output : display log text if client login                        //
// Purpose : client implementing login function with accessible IP  //
//////////////////////////////////////////////////////////////////////

#define TRUE 1
#define MAX_BUF 20

//define functions
void initialize(char buff[], int length);
void log_in(int sockfd);

// main function
int main(int argc, char *argv[]){
    char buff[MAX_BUF];
    int sockfd;
    struct sockaddr_in server;

    // exception handling
    if(argc != 3){
        printf("Client takes two arguments only.\n"); // client takes only IP address and Port number
        return 0;
    }

    ////////////// CLIENT Implementation //////////////
    // 1. create socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // IPv4 Internet Domain, connection-oriented
        perror("socket");
        exit(1);
    }
    
    memset(&server, 0, sizeof(server)); // initialize server memory
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]); // server IP address client willing to connect
    server.sin_port = htons(atoi(argv[2])); // server port number client willing to connect

    // 2. connect
    if(connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1){ // client requests a connection to server
        printf("Invalid Port number.\n");
        return 0;
    }

    // 3. read (receive)
    initialize(buff, MAX_BUF); // initialize buffer before read
    if(read(sockfd, buff, MAX_BUF) > 0){ // reading has succeeded from sockfd to buff
        if(!strcmp(buff, "ACCEPTED")){ // if server sent ACCEPTED 
            // 4. try log-in
            log_in(sockfd); // call log_in function
        }
        else if (!strcmp(buff, "REJECTION")){ // if server sent REJECTION, failed to connect login
            printf("**Connect refused**\n");
            close(sockfd); // close process
        }
    }
    return 0;
}

////////////// function to log-in to server as client //////////////
void log_in(int sockfd){
    int n;
    char *user[MAX_BUF], *passwd, buf[MAX_BUF];

    while(1){
        // 4.1 pass username to server
        *user = getpass("\nInput ID : "); // turn off echoing to get user ID, enter ID
        printf("%s\n", *user);

        char cp_user[MAX_BUF];
        strcpy(cp_user, *user); // variable to print user name if success
        write(sockfd, *user, MAX_BUF); // send user ID to server

        passwd = getpass("Input Password : "); // turn off echoing to get password
        printf("%s\n", passwd);
        write(sockfd, passwd, MAX_BUF); // send password to server

        // 4.2  compare received code from server and display result
        n = read(sockfd, buf,  MAX_BUF); 
        buf[n] = '\0';

        if(!strcmp(buf, "OK")){ // Server sent OK
            // code : login succes
            printf("** User '[%s]' logged_in **\n", cp_user); // display user ID
            break; // break loop
        }
        else if(!strcmp(buf, "FAIL")){ // Server sent FAIL
            // code : login fail
            printf("** Log-in failed **\n"); // can try log-in upto three times
        }
        else{ // buf is DISCONNECTION
            // code : three times fail
            printf("** Connection closed **\n");
            close(sockfd); // close socket process
            break;
        } 
    }
}

////////////// function to initialize buffer //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
}
