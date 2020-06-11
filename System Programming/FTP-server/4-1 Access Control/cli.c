#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
//#include <signal.h>

#define MAX_BUF 20
#define CONT_PORT   2000
#define TRUE 1

//define functions
void log_in(int sockfd);
void initialize(char buff[], int length);


int main(int argc, char *argv[]){
    char buff[MAX_BUF], cmd_buff[MAX_BUF], rcv_buff[MAX_BUF];
    int sockfd, n, p_pid;
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
    initialize(rcv_buff, MAX_BUF); // initialize buffer before read
    if(read(sockfd, rcv_buff, MAX_BUF) > 0){ // reading has succeeded from sockfd to buff
        if(!strcmp(rcv_buff, "ACCEPTED")){
            printf("from server : %s\n", rcv_buff); 
            log_in(sockfd);
        }
        else if (!strcmp(rcv_buff, "REJECTION")){
            printf("**Connect refused**\n");
            close(sockfd);
        }
    }
    return 0;
}

void log_in(int sockfd){
    int n;
    char *user[MAX_BUF], *passwd, buf[MAX_BUF];

    while(1){
        // code : pass username to server
        *user = getpass("Input ID : "); // turn off echoing to get user ID
        printf("%s\n", *user);
        char cp_user[MAX_BUF];
        strcpy(cp_user, *user);
        write(sockfd, *user, MAX_BUF);

        passwd = getpass("Input Password : "); // turn off echoing to get user ID
        printf("%s\n", passwd);
        write(sockfd, passwd, MAX_BUF);

        n = read(sockfd, buf,  MAX_BUF);
        buf[n] = '\0';

        if(!strcmp(buf, "OK")){ // server send OK
            // code : login succes
            printf("** User '[%s]' logged_in **\n", cp_user);
            break;
        }
        else if(!strcmp(buf, "FAIL")){ // Server sent FAIL
            // code : login fail
            printf("** Log-in failed **\n");
        }
        else{ // buf is DISCONNECTION
            // code : three times fail
            printf("** Connection closed **\n");
            break;
        } 
    }
    close(sockfd);
}

////////////// function to initialize //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
}
