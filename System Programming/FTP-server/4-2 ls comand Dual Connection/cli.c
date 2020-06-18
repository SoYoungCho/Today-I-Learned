//////////////////////////////////////////////////////////////////////
// File Name    : cli.c                                             //
// Date         : 2020/06/18                                        //
// Os           : Ubuntu 18.04.4 LTS 64bits                         //
// Author       : Cho So Young                                      //
// Student ID   : 2017204050                                        //
// ---------------------------------------------------------------- //
// Title : System Programming Assiginment #4-2 (client)             //
// Description : Implementation of Split connection                 //
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Program of implemented split connection                          //
// ================================================================ //
// Input : IP address and port number, ls command                   //
// Output : display numerical response message, command result      //
// Purpose : client implementing split connection (control & data)  //
//////////////////////////////////////////////////////////////////////

#define MAX_BUF 512
#define INIT_SIZE 32

#define SENT_REPLY_CODE "226 Result is sent successfully.\n"

//define functions
char* convert_addr_to_str(unsigned long ip_addr, unsigned int port);
int host_data_conncection(char *hostport);
char** split(char *string, char separator, int *num_tokens);
char* str(int size);
void initialize(char buf[], int length);

// main function
int main(int argc, char **argv){
    char *hostport;
    int sockfd;
    struct sockaddr_in temp;
    char buf[MAX_BUF], cmd_buf[MAX_BUF], rcv_buf[MAX_BUF], tmp[MAX_BUF];
    srand(time(0));

    // exception handling
    if(argc != 3){
        printf("Client takes two arguments.\n"); // client takes only IP address and Port number
        return 0;
    }

    ////////////// CLIENT Implementation //////////////
    // 1. create socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // IPv4 Internet Domain, connection-oriented
        perror("socket");
        exit(1);
    }
    
    memset(&temp, 0, sizeof(temp)); // initialize server memory
    temp.sin_family = AF_INET;
    temp.sin_addr.s_addr = inet_addr(argv[1]); // server IP address client willing to connect
    temp.sin_port = htons(atoi(argv[2])); // server port number client willing to connect

    // 2. connect   
    if(connect(sockfd, (struct sockaddr*)&temp, sizeof(temp)) == -1){ // client requests a connection to server
        printf("Invalid Port number.\n");
        return 0;
    }

    // 3. enter ls command
    printf("\n> ");
    initialize(cmd_buf, MAX_BUF);
    fgets(cmd_buf, MAX_BUF, stdin); // client enters command "ls"
    cmd_buf[strlen(cmd_buf)-1] = '\0';
    
    int cmd_len = strlen(cmd_buf);

    if(!strcmp(cmd_buf, "ls")){ // user enters ls command
        write(sockfd, cmd_buf,  MAX_BUF); // send ls command to server
        hostport = convert_addr_to_str(temp.sin_addr.s_addr, temp.sin_port); // convert address to string
        strcpy(tmp, hostport);

        write(sockfd, hostport, MAX_BUF); // send converted PORT message to server
        read(sockfd, rcv_buf, MAX_BUF); // receive PORT_REPLY_CODE
        printf("%s\n",rcv_buf); // print PORT_REPLY_CODE

        host_data_conncection(tmp); // call host_data_connection function
    }
    else{ // if user does not enter ls command
        printf("Unsupported command %s\n",cmd_buf);
        write(sockfd, "UNKNOWN", strlen("UNKNOWN"));
    }
}

////////////// function to convert client IP and randomly generated port num in to string //////////////
char * convert_addr_to_str(unsigned long ip_addr, unsigned int port){
    // function returning ip address and random port number beside PORT command
    char *addr= (char *)&ip_addr;
    char ip_str[30] = {'\0'};
    int quotient, remainder;
    
        int rand_port = rand()%20000 + 10001; // random sample port number between 10001 ~ 30000

    quotient = rand_port >> 8; // same as divided by 2^8
    remainder = rand_port % 256; // remainder divided by 256

    sprintf(ip_str, "PORT %d,%d,%d,%d,%d,%d", addr[0], addr[1], addr[2], addr[3], quotient, remainder); // make attatched string 
    addr = ip_str; // return converted string
    return addr; 
}

////////////// function to make data connection as host //////////////
int host_data_conncection(char *hostport){
    char ip[20];
    char port[20];

    char buf[MAX_BUF];
    struct sockaddr_in host, guest; // socket address structure for server and client
    int listenfd, connfd, guest_len = sizeof(guest);

    char **tokens;
    int num_tokens = 0;

    tokens = split(hostport, ' ', &num_tokens); // split hostport with blank
    char **ip_with_port = split(tokens[1], ',', &num_tokens); // split right-side with commar

    sprintf(ip, "%s.%s.%s.%s", ip_with_port[0], ip_with_port[1], ip_with_port[2], ip_with_port[3]); // combine ip
    sprintf(port, "%d", atoi(ip_with_port[4]) * 256 + atoi(ip_with_port[5])); // combine port numb with simple transformation

    // 1. create socket
    if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    memset(&host, 0, sizeof(host)); // initialize server memory
    host.sin_family           = AF_INET;
    host.sin_addr.s_addr      = inet_addr(ip); // host IP address
    host.sin_port             = htons(atoi(port)); // host port number

    // 2. bind
    if(bind(listenfd, (struct sockaddr*)&host, sizeof(host)) == -1){;  // associate and address with a socket. sd is server socket descriptor
        perror("bind"); // exception handling
        exit(1);
    }

    // 3. listen
    if(listen(listenfd, 5) == -1){ // willing to accept connect request
        perror("listen"); // exception handling
        exit(1);
    }

    // 4. accept
    connfd = accept(listenfd, (struct sockaddr *)&guest, &guest_len); // accept a connect request from guest
    
    initialize(buf, MAX_BUF); // initialize buffer
    read(connfd, buf, MAX_BUF); // receive data from guest descriptor connfd in buff
    printf("%s\n",buf); // print received file name as result for ls command
    int count = 0;

    for (int i = 0; i < strlen(buf); i++){ // count files
        if (buf[i] == '\n')
            count++;
    }

    write(connfd, SENT_REPLY_CODE, strlen(SENT_REPLY_CODE)); // send code to guest
    printf("%s", SENT_REPLY_CODE); // print sent message code
    printf("OK. %ld bytes are received.\n", strlen(buf) * sizeof(char) - count * sizeof(char)); // calculate size and print
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
