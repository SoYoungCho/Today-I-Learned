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


//////////////////////////////////////////////////////////////////////
// Program of implemented split connection                          //
// ================================================================ //
// Input : IP address and port number, ls command                   //
// Output : display numerical response message, command result      //
// Purpose : client implementing split connection (control & data)  //
//////////////////////////////////////////////////////////////////////

#define TRUE 1
#define MAX_BUF 20
#define INIT_SIZE 64

//define functions
char* convert_addr_to_str(unsigned long ip_addr, unsigned int port);
void initialize(char buff[], int length);
int data_conncection(char *hostport);
char** split(char *string, char separator, int *num_tokens);
char* str(int size);

// main function

int main(int argc, char **argv){
    char *hostport;
    int sockfd;
    struct sockaddr_in temp;
    char buff[MAX_BUF], cmd_buff[MAX_BUF], rcv_buff[MAX_BUF];
    pid_t childpid;
    // my code

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
    
    memset(&temp, 0, sizeof(temp)); // initialize server memory
    temp.sin_family = AF_INET;
    temp.sin_addr.s_addr = inet_addr(argv[1]); // server IP address client willing to connect
    temp.sin_port = htons(atoi(argv[2])); // server port number client willing to connect

    // 2. connect   
    if(connect(sockfd, (struct sockaddr*)&temp, sizeof(temp)) == -1){ // client requests a connection to server
        printf("Invalid Port number.\n");
        return 0;
    }
    printf("connect complete\n");

    // 3. enter ls command
    printf("\nInput command : ");
    fgets(cmd_buff, MAX_BUF, stdin); // client enters command
    cmd_buff[strlen(cmd_buff)-1] = '\0';
    int cmd_len = strlen(cmd_buff);

    if(!strcmp(cmd_buff, "ls")){ // user enters ls command
        hostport = convert_addr_to_str(temp.sin_addr.s_addr, temp.sin_port);
        write(sockfd, hostport, strlen(hostport)); // send PORT message, IP and port num
        data_conncection(hostport);
    }
    else{
        printf("Unsupported command %s\n",cmd_buff);
        write(sockfd, "UNKNOWN", strlen("UNKNOWN"));
    }

    // 4. send ls command to server
    //write(sockfd, cmd_buff, cmd_len); // send ls command to server
    //send(sockfd, cmd_buff, cmd_len, 0); // send command to server
    //printf("client writes %s %d\n", cmd_buff, cmd_len);
    //initialize(rcv_buff, MAX_BUF); // initialize buffer

    //int n = read(sockfd, rcv_buff,  MAX_BUF);     

    //process_result(sd, cmd_buff, rcv_buff, cmd_len); // call process result funtion

}

char * convert_addr_to_str(unsigned long ip_addr, unsigned int port){
    // function returning ip address and random port number beside PORT command
    char *addr= (char *)&ip_addr;
    char ip_str[30] = {'\0'};
    int quotient, remainder;

    int rand_port = rand()%20000 + 10001; // random sample port number between 10001 ~ 30000

    quotient = rand_port >> 8; // same as divided by 2^8
    remainder = rand_port % 256; // remainder divided by 256

    sprintf(ip_str, "PORT %d,%d,%d,%d,%d,%d", addr[0], addr[1], addr[2], addr[3], quotient, remainder);
    printf("ip address: %s\n", ip_str);
    addr = ip_str;
    return addr; 
}



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


char* str(int size){
	char *string = (char*)malloc(sizeof(char) * size);

	for (int i = 0; i < size; i++)
		string[i] = '\0';

	return string;
}

int data_conncection(char *hostport){
    char ip[20];
    char port[20];

    char buff[MAX_BUF], result_buff[MAX_BUF];
    struct sockaddr_in svr_like_cli, cli_like_svr; // socket address structure for server and client
    int listenfd, connfd, cli_len = sizeof(cli_like_svr);
    int n;

    char **tokens;
    int num_tokens = 0;

    printf("hostport : %s\n", hostport);
    // PORT 127,0,0,1,78,54 

    tokens = split(hostport, ' ', &num_tokens);
    char **ip_with_port = split(tokens[1], ',', &num_tokens);
    for(int i =0; i<num_tokens; i++){
        printf("%s ", ip_with_port[i]);
    }

    sprintf(ip, "%s.%s.%s.%s", ip_with_port[0], ip_with_port[1], ip_with_port[2], ip_with_port[3]);
    printf("ip : %s", ip);
    sprintf(port, "%d", atoi(ip_with_port[4]) * 256 + atoi(ip_with_port[5]));
    printf("port : %s", port);

    getchar();
    // (2) split IP and port num part with comma

/* 
    // 1. create socket
    if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    

    
    memset(&svr_like_cli, 0, sizeof(svr_like_cli)); // initialize server memory
    svr_like_cli.sin_family           = AF_INET;
    svr_like_cli.sin_addr.s_addr      = htonl(INADDR_ANY); // server IP address, find automatically
    svr_like_cli.sin_port             = htons(atoi(argv[1])); // server port number

    // 2. bind
    if(bind(listenfd, (struct sockaddr*)&svr_like_cli, sizeof(svr_like_cli)) == -1){;  // associate and address with a socket. sd is server socket descriptor
        perror("bind"); // exception handling
        exit(1);
    }

    // 3. listen
    if(listen(listenfd, 5) == -1){ // willing to accept connect request
        perror("listen"); // exception handling
        exit(1);
    }

    // 4. accept
    connfd = accept(listenfd, (struct sockaddr *)&cli_like_svr, &cli_len); // accept a connect request from client
    host_ip = client_info(&cli_like_svr); // display client ip and port

    */
}



////////////// function to initialize buffer //////////////
void initialize(char buff[], int length){
    for(int i = 0; i < length; i++)
        buff[i] = '\0';
    return;
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

/*
char *itos(int num){



}*/