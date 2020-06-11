//////////////////////////////////////////////////////////////////////
// File Name    : srv.c                                             //
// Date         : 2020/06/11                                        //
// Os           : Ubuntu 18.04.4 LTS 64bits                         //
// Author       : Cho So Young                                      //
// Student ID   : 2017204050                                        //
// ---------------------------------------------------------------- //
// Title : System Programming Assiginment #4-1 (server)             //
// Description : Implementation of Access Control and User Authentication//
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
// Program of implementing access control and user authentication   //
// ================================================================ //
// Input : port number                                              //
// Output : display log text                                        //
// Purpose : server implementing login function with accessible IP  //
//////////////////////////////////////////////////////////////////////


#define MAX_BUF 20
#define TRUE 1
#define FALSE 0
#define USER_TEXT ("access.txt")

//define functions
char *client_info(struct sockaddr_in *client);
int check_ip(char *client_ip);
int log_auth(int connfd);
int user_match(char *user, char *passwd);

// main function
int main(int argc, char *argv[]){ 
    char *client_ip;
    int listenfd, connfd;
    struct sockaddr_in server, client;
    int cli_len;

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
        cli_len = sizeof(client); // length of socket address

        // 4. accept and display client info
        connfd = accept(listenfd, (struct sockaddr *)&client, &cli_len); // accept a connect request from client
        client_ip = client_info(&client); // display client ip and port

        // 5. check IP accessibility
        int check_result = check_ip(client_ip); // call check_ip function

        if(check_result == TRUE){ // IP accessible
            write(connfd, "ACCEPTED", strlen("ACCEPTED")); // send to client
            printf("** Client is connected **\n");
        }
        else if(check_result == FALSE){ // IP unaccessible
            write(connfd, "REJECTION", strlen("REJECTION")); // send to client
            printf("** It is NOT authenticated client **\n");
            close(connfd);
            continue;
        }

        // 6. check User Authentication
        if(log_auth(connfd) == 0){ // if 3 time fail (ok : 1, fail : 0)
            printf("** Fail to log-in **\n");
            close(connfd); // close process connection
            continue;
        }
        // User Authentication Ok
        printf("** Success to log-in **\n"); 
    }

    return 0;
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


////////////// function to check accessibility of IP address //////////////
int check_ip(char *client_ip){
    char buf[MAX_BUF];
    char *pStr;
    int flag = FALSE;

    FILE *fp_checkIP; // File stream to check client's IP
    fp_checkIP = fopen(USER_TEXT, "r"); // read "access.txt" file

    if(fp_checkIP != NULL) { 
        char *cmptokens[4];
        cmptokens[0] = strtok(client_ip, "."); // split client IP with "." and save
        cmptokens[1] = strtok(NULL, ".");
        cmptokens[2] = strtok(NULL, ".");
        cmptokens[3] = strtok(NULL, ".");

        while( (pStr = fgets(buf, sizeof(buf), fp_checkIP)) != NULL){ // read in line
            char *tokens[4];
            tokens[0] = strtok(pStr, "."); // split lines in "access.txt" with "." and save
            tokens[1] = strtok(NULL, ".");
            tokens[2] = strtok(NULL, ".");
            tokens[3] = strtok(NULL, "\n");

            for(int i = 0; i < 4; i++){ // compare every splited tokens
                if(!strcmp(tokens[i], cmptokens[i])){ // if same token
                    flag = TRUE;
                    continue;
                }
                else if(!strcmp(tokens[i],"*")){ // or token is "*" (wildcard)
                    flag = TRUE;
                    continue;
                }
                else{ // neither above
                    flag = FALSE;
                    break;
                }
            }

            if(flag){ // if client IP is in "access.txt"
                fclose( fp_checkIP ); // close file
                return TRUE;
            }
        } 
    }
    fclose( fp_checkIP ); // if client IP is not in "access.txt"
    return FALSE;
}

////////////// function to check Log-in User Authentication  //////////////
int log_auth(int connfd){
    char user[MAX_BUF], passwd[MAX_BUF]; // variable to save client's ID and passwd
    int n, count = 1;

    while(1){ 
        printf("\n** User is trying to log-in (%d/3) **\n", count);

        // 6.1 receive username and password from client
        read(connfd, user, MAX_BUF); // receive user ID from client
        read(connfd, passwd, MAX_BUF); // receive user password from client

        // 6.2 call user_match function to match user
        if((n = user_match(user, passwd)) == 1){
            write(connfd, "OK", MAX_BUF);  // code : verification OK, send to client
            return 1;
        }
        else if(n==0){
            printf("** Log-in failed **\n");
            if(count >= 3){
                write(connfd, "DISCONNECTION", MAX_BUF); // code : three times fail, send to client
                return 0;
            }
            write(connfd, "FAIL", MAX_BUF); // code : FAIL, send to client
            count++;
            continue;
        }
    }
}

////////////// function to match user  //////////////
int user_match(char *user, char *passwd){
    FILE *fp; // FILE stream to check client's IP
    struct passwd *pw; // passwd structure

    // 6.2.1 open and read passwd file
    fp = fopen("passwd", "r");

    // 6.2.2 compare whether ID and passwd matches
    while((pw = fgetpwent(fp)) != NULL){ // get passwd file entry
        if(!strcmp(user, pw->pw_name)){ // name in struct pw
            if(!strcmp(passwd, pw->pw_passwd)){ // success in verification, return 1.
                return 1;
            }
            else{  // name in struct pw but passwd not in struct
                continue;
            }
        }
        else{ // name not in struct pw
            continue;
        }
    }
    return 0; // if fails, return 0 (do not match)
}
