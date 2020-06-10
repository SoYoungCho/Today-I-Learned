#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <fcntl.h>
//#include <signal.h>

#define MAX_BUF 20
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define USER_TEXT ("access.txt")

//define functions
int log_auth(int connfd);
int user_match(char *user, char *passwd);
char *client_info(struct sockaddr_in *client);
int check_ip(char *client_ip);

int main(int argc, char *argv[]){ 
    char *client_ip;
    int listenfd, connfd;
    struct sockaddr_in server, client;
    int cli_len;

    //FILE *fp_checkIP; // File stream to check client's IP

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

        // 4. accept
        connfd = accept(listenfd, (struct sockaddr *)&client, &cli_len); // accept a connect request from client

        client_ip = client_info(&client); // display client ip and port

        // code : check if client's IP accessible
        if(check_ip(client_ip) == TRUE){
            write(connfd, "ACCEPTED", strlen("ACCEPTED"));
            printf("** Client is connected **\n");
            
        }
        else if(check_ip(client_ip) == FALSE){
            write(connfd, "REJECTION", strlen("REJECTION"));
            printf("** It is NOT authenticated client **\n");
        }

        getchar();
        
        /*
        if(log_auth(connfd) == 0){ // if 3 time fail (ok : 1, fail : 0)
            printf("** Fail to log-in **\n");
            close(connfd);
            continue;
        }
        printf("** Success to log-in **\n");
        close(connfd);
        */
    }

    return 0;
}

int log_auth(int connfd){
    char user[MAX_BUF], passwd[MAX_BUF];
    int n, count = 1;

    while(1){
        // code : receive username and password from client
        write(connfd, "OK", MAX_BUF);

        if((n = user_match(user, passwd)) == 1){
            // code : verification OK
        }

        else if(n==0){
            if(count >= 3){
                // code : three times fail
            }
            write(connfd, "FAIL", MAX_BUF);
            count++;
            continue;
        }
    }
    return 1;
}

int user_match(char *user, char *passwd){
    
    FILE *fp;
    struct passwd *pw;

    fp = fopen("passwd", "r");

    // code : if success in verification, return 1.
    // if fails, return 0
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

 int check_ip(char *client_ip){
    char buf[MAX_BUF];
    char *pStr;
    int flag = FALSE;

    FILE *fp_checkIP; // File stream to check client's IP

    fp_checkIP = fopen(USER_TEXT, "r"); // read access.txt file
    if(fp_checkIP != NULL) {
        char *pStr;
        char *cmptokens[4];
        cmptokens[0] = strtok(client_ip, ".");
        cmptokens[1] = strtok(NULL, ".");
        cmptokens[2] = strtok(NULL, ".");
        cmptokens[3] = strtok(NULL, ".");

        while(!feof(fp_checkIP)){
            pStr = fgets( buf, sizeof(buf), fp_checkIP );
            printf( "%s", pStr );
            char *tokens[4];
            tokens[0] = strtok(pStr, ".");
            tokens[1] = strtok(NULL, ".");
            tokens[2] = strtok(NULL, ".");
            tokens[3] = strtok(NULL, "\n");

            for(int i = 0; i<4; i++){
                if(!strcmp(tokens[i], cmptokens[i])){ // same token
                    flag = TRUE;
                    continue;
                }
                else if(!strcmp(tokens[i],"*")){
                    flag = TRUE;
                    continue;
                }
                else{
                    flag = FALSE;
                    break;
                }
            }

            if(flag){
                fclose( fp_checkIP );
                return TRUE;
            }

            getchar();
        }
        
    }
    fclose( fp_checkIP );
    return FALSE;
}

