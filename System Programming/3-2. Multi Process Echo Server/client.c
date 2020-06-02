//////////////////////////////////////////////////////////////////////
// Os           : Ubuntu 18.04.4 LTS 64bits                         //
// Author       : Cho So Young                                      //
// ---------------------------------------------------------------- //
// TTitle : Advanced Echo Server                                    //
// Description : Implementation of advanced echo server using fork()//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>

//////////////////////////////////////////////////////////////////////
// Program of implementing echo server using socket (client part)   //
// ================================================================ //
// Input : IP address and port number                               //
// Output : return echo result sent and received from server        //
// Purpose : client using socket(), connect() etc.                  //
//////////////////////////////////////////////////////////////////////

#define BUF_SIZE 256
#define TRUE 1

// define functions
void initialize(char buff[], int length);

// main function
int main(int argc, char **argv){
    char buff[BUF_SIZE], cmd_buff[BUF_SIZE], rcv_buff[BUF_SIZE];
    int sd;
    struct sockaddr_in server; // sockect address structure for server
    int cmd_len;

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
    
    memset(&server, 0, sizeof(server)); // initialize server memory
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]); // server IP address client willing to connect
    server.sin_port = htons(atoi(argv[2])); // server port number client willing to connect

    // 2. connect
    if(connect(sd, (struct sockaddr*)&server, sizeof(server)) == -1){ // client requests a connection to server
        printf("Invalid Port number.\n");
        return;
    }

    /* open socket and connect to server */

    while(TRUE){
        write(STDOUT_FILENO, "> ", 2);

        if(fgets(cmd_buff, BUF_SIZE, stdin) != NULL){ // client enters command
            cmd_buff[strlen(cmd_buff)-1] = '\0'; // add NULL at the end of cmd_buff
            cmd_len = strlen(cmd_buff);

            // 3. write (send)
            if(write(sd, cmd_buff, cmd_len) > 0){ // writing buff to socket file descriptor has succeeded
                initialize(rcv_buff, BUF_SIZE); // initialize buffer

                // 4. read (receive)
                if(read(sd, rcv_buff, BUF_SIZE) > 0){ // reading has succeeded from sockfd to buff
                    printf("from server : %s\n", rcv_buff); // echo. print command sent and received from server
                    continue;
                }
                else // failed to read
                    write(sd, "QUIT",strlen("QUIT")); // send "QUIT" to server to disconnect
            }
            else // failed to write
                write(sd, "QUIT", strlen("QUIT")); // send "QUIT" to server to disconnect
        }
        else{ // failed to enter command
            write(sd, "QUIT",strlen("QUIT")); // send "QUIT" to server to disconnect
        }
        break; // break loop if "QUIT"
    }
    // 5. close
    close(sd); // close client process
    return 0;
}

////////////// function to initialize //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
}
