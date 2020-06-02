//////////////////////////////////////////////////////////////////////
// Os           : Ubuntu 18.04.4 LTS 64bits                         //
// Author       : Cho So Young                                      //
// Student ID   : 2017204050                                        //
// ---------------------------------------------------------------- //
// Title : Advanced Echo Server                                     //
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
// Program of implementing echo server using socket                 //
// ================================================================ //
// Input : port number                                              //
// Output : return result for client request                        //
// Purpose : server using fork() and etc                            //
//////////////////////////////////////////////////////////////////////

#define BUF_SIZE 256
#define ALARM_SEC 3
#define TRUE 1

// define functions
void sh_chld(int); // signal handler for SIGCHLD
void sh_alrm(int); // signal handler for SIGALRM
char *client_info(struct sockaddr_in *client);
int Fork();
void initialize(char buff[], int length);

// main function
int main(int argc, char **argv){
    char buff[BUF_SIZE];
    struct sockaddr_in server, client; // sockect address structure for server and client
    int sd, cd;
    pid_t childpid;
    int cli_len;

    signal(SIGALRM, sh_alrm); // signal handler(sh_alarm) for SIGALRM
    signal(SIGCHLD, sh_chld); // signal handler(sh_chld) for SIGCHLD

    ////////////// SERVER Implementation //////////////
    // 1. create socket
    if((sd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    memset(&server, 0, sizeof(server)); // initialize server memory
    server.sin_family           = AF_INET;
    server.sin_addr.s_addr      = htonl(INADDR_ANY); // server IP address, find automatically
    server.sin_port             = htons(atoi(argv[1])); // server port number

    // 2. bind
    if(bind(sd, (struct sockaddr*)&server, sizeof(server)) == -1){;  // associate and address with a socket. sd is server socket descriptor
        perror("bind"); // exception handling
        exit(1);
    }

    // 3. listen
    if(listen(sd, 5) == -1){ // willing to accept connect request
        perror("listen"); // exception handling
        exit(1);
    }

    // wait for client. blocked until request connect
    while(TRUE){
        pid_t pid;
        cli_len = sizeof(client);

        // 4. accept
        cd = accept(sd, (struct sockaddr*)&client, &cli_len); // accept a connect request from client
        printf("Connction accepted with new process.\n");
        
        printf("process : %d : allocated! \n", (int)getpid());
        char *client_ip = client_info(&client); // display client ip and port

        //////////////// Create Child Server Process ////////////////
        if( (childpid = Fork()) == 0){ // child server process (made by fork)
            //printf("process : %d : allocated! \n", (int)getpid());

            //char *client_ip = client_info(&client); // display client ip and port

            while(TRUE){
                initialize(buff, BUF_SIZE); // initialize buffer

                // 5. read
                read(cd, buff, BUF_SIZE); // receive data from client descriptor cd in buff
                
                // when client sends 'quit' or raises error
                if(!strcmp(buff, "QUIT")){ // disconnect with client, call SIGALRM signal to end that process as well
                    sh_alrm(ALARM_SEC); // signal handler for SIGALRM
                }
                // when receives normally
                else{ 
                    // 6. write
                    write(cd, buff, strlen(buff));   
                }
            }
        }
        // 7. close forked child process
        close(cd);
    }
    return 0;
}

/////// wrapper function for fork(), handling exception ///////
int Fork(){
    pid_t childpid;
    if((childpid = fork()) < 0){ // exception handling
        perror("fork");
        return -1; // error
    }
    else{ // return 0 if child process, otherwise return child process's pid to parent
        return (int)childpid; 
    }
}

////////////// function to initialize //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
}

//////////////  signal handler(sh_alarm) for SIGALRM //////////////
void sh_alrm(int signum){
    printf("Child Process (PID : %d) will be terminated.\n", getpid());
    exit(1);
}

//////////////// signal handler for SIGCHLD //////////////
void sh_chld(int signum){
    printf("Status of Child process was changed.\n\n");
    wait(NULL);
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
