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
#include <dirent.h>

//////////////////////////////////////////////////////////////////////
// Program of implemented split connection                          //
// ================================================================ //
// Input : port number                                              //
// Output : display port info, numerical response message           //
// Purpose : server implementing split connection (control & data)  //
//////////////////////////////////////////////////////////////////////

#define INIT_SIZE 32
#define MAX_BUF 512

#define PORT_REPLY_CODE "200 Port command successful\n"
#define OPEN_REPLY_CODE "150 Opening data connection for directory list\n"

//define functions
char* convert_str_to_addr(char *str, unsigned int *port);
int guest_data_connection(char *host_ip, unsigned int port_num);
int cmd_process(char cmd_buf[], char result_buf[], int sd);
char** split(char *string, char separator, int *num_tokens);
char* str(int size);
void initialize(char buf[], int length);
void initialize_(char * buf, int length);

 // main function
int main(int argc, char **argv){ 
    char *host_ip;
    char *cli_ip;
    int listenfd, connfd;
    struct sockaddr_in server, client;
    int cli_len;
    unsigned int port_num;
    char buf[MAX_BUF], cmd_buf[MAX_BUF];

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
    initialize(cmd_buf, MAX_BUF); // initialize buffer
    
    cli_len = sizeof(client); // length of socket address

    // 4. accept and display client info
    connfd = accept(listenfd, (struct sockaddr *)&client, &cli_len); // accept a connect request from client

    // 5-1. read ls command
    read(connfd, cmd_buf, MAX_BUF); // ls command

    // 5-2. read PORT msg
    initialize(buf, MAX_BUF); // initialize buffer
    read(connfd, buf, MAX_BUF); // read PORT message
    printf("%s \n", buf);
    
    printf(PORT_REPLY_CODE); // print PORT_REPLY_CODE
    write(connfd, PORT_REPLY_CODE, strlen(PORT_REPLY_CODE)); // send PORT_REPLY_CODE tp client
    printf("%s\n", cmd_buf); // print ls command
    host_ip = convert_str_to_addr(buf, (unsigned int *)&port_num); // call function to convert string into address

    guest_data_connection(host_ip, port_num); // call guest_data_connection function    
}

char* convert_str_to_addr(char *string, unsigned int *port){
    // change IP address and port num in PORT command received from client
    char *addr;
    char ip[20];
    char tmp_port[20];
    
    char **tokens;
    int num_tokens = 0;

    tokens = split(string, ' ', &num_tokens); // split string with blank space
    char **ip_with_port = split(tokens[1], ',', &num_tokens); // split right-side with commar

    sprintf(ip, "%s.%s.%s.%s", ip_with_port[0], ip_with_port[1], ip_with_port[2], ip_with_port[3]); // make attached string IP
    sprintf(tmp_port, "%d", atoi(ip_with_port[4]) * 256 + atoi(ip_with_port[5])); // convert string port number through calculation

    addr = str(strlen(ip));
    strcpy(addr,ip);
    *port = atoi(tmp_port); // set port number

    return addr; // retuern converted address
}

int guest_data_connection(char *host_ip, unsigned int port_num){
    int sockfd;
    char buf[MAX_BUF], cmd_buf[MAX_BUF], result_buf[MAX_BUF];
    struct sockaddr_in host;

    ////////////// GUEST Implementation //////////////
    // 1. create socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // IPv4 Internet Domain, connection-oriented
        perror("socket");
        exit(1);
    }

    memset(&host, 0, sizeof(host)); // initialize host memory
    host.sin_family = AF_INET;
    host.sin_addr.s_addr = inet_addr(host_ip); // host IP address guest willing to connect
    host.sin_port = htons(port_num); // host port number guest willing to connect
    sleep(1); // wait for a second

    // 2. connect   
    if(connect(sockfd, (struct sockaddr*)&host, sizeof(host)) == -1){ // guest requests a connection to host
        printf("Connect Error.\n");
        return 0;
    }
    
    printf(OPEN_REPLY_CODE); // print OPEN_REPLY_CODE
    write(sockfd, OPEN_REPLY_CODE, strlen(OPEN_REPLY_CODE)); // send OPEN_REPLY_CODE to host
    
    cmd_process(cmd_buf, result_buf, sockfd); // call function to process ls command
    close(sockfd);
    return 0;
}

////////////// function to process result //////////////
int cmd_process(char cmd_buf[], char result_buf[], int sd){    
    DIR* dp;
    struct dirent* dirp;
    char arr[MAX_BUF];
    int num_tokens = 0;

    char ** tokens;
    tokens = split(cmd_buf, ' ', &num_tokens); // split command with blank space

    initialize(arr, MAX_BUF);

    if((dp = opendir(".")) != NULL){ // use opendir() and open
        initialize(result_buf, MAX_BUF); // initialize result_buf

        while((dirp = readdir(dp)) != NULL){ // use readdir() to read file names
            if (dirp -> d_ino != 0){

                if(strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")){ // exception with dot and dot-dot dir
                    char *tmp = strcat(dirp->d_name, "\n");

                    if (strlen(arr) == 0){
                        strcpy(arr, tmp);
                    }
                    else{
                        strcat(arr, tmp);
                    } 
                }
            }
        }    
        write(sd, arr, MAX_BUF); // send file names to host
        closedir(dp); // close directory
    }
    else{ // exception handling when pathname can not be opened
        printf("can't open.\n");
    }
    
    initialize(cmd_buf, MAX_BUF);
    read(sd, cmd_buf, MAX_BUF); // receive command from host
    printf("%s", cmd_buf); // print command
    return 0;
}

////////////// function to split string with separator //////////////
char** split(char *string, char separator, int *num_tokens){
	char **tokens;
	int *lengths;
	int tokens_idx = 0, token_idx = 0;
	*num_tokens = 1;

	for (int i = 0; i < strlen(string); i++){
		if (string[i] == separator)
			(*num_tokens)++;
	}

	lengths = (int*)malloc(sizeof(int) * (*num_tokens));
	tokens = (char**)malloc(sizeof(char*) * (*num_tokens));

	for (int i = 0; i < *num_tokens; i++){
		tokens[i] = str(INIT_SIZE);
		lengths[i] = INIT_SIZE;
	}

	for(int i = 0; i < strlen(string); i++){
		if (string[i] == separator && strlen(tokens[tokens_idx]) != 0){
			token_idx = 0;
			tokens_idx++;
		}
		else if (string[i] == separator && strlen(tokens[tokens_idx]) == 0){
			continue;
		}
		else{
			/* Memory reallocation, If array is full. */
			if (strlen(tokens[tokens_idx]) == lengths[tokens_idx] - 1){
				int length = (lengths[tokens_idx] * sizeof(char)) << 1;
				tokens[tokens_idx] = (char*)realloc(tokens[tokens_idx], length);

				for (int j = lengths[tokens_idx]; j < lengths[tokens_idx] << 1; j++)
					tokens[tokens_idx][j] = '\0';

				lengths[tokens_idx] <<= 1;
			}

			tokens[tokens_idx][token_idx] = string[i];
			token_idx++;
		}
	}

	free(lengths);
	return tokens;
}

////////////// function to initialize with dynamic allocation //////////////
char* str(int size){
	char *string = (char*)malloc(sizeof(char) * size);

	for (int i = 0; i < size; i++)
		string[i] = '\0';

	return string;
}

////////////// function to initialize buffer //////////////
void initialize(char buf[], int length){
    for(int i = 0; i < length; i++)
        buf[i] = '\0';
    return;
} 

////////////// function to initialize char pointer type buffer //////////////
void initialize_(char *buf, int length){
    for(int i = 0; i < length; i++)
        buf[i] = '\0';
    return;
} 
