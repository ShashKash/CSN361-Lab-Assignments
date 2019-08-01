/** @file Q1_server.c
 * @brief Solution of Question 1 of LA2. Code for server.
 *
 * @author Shashank
 *
 * @date 7/31/2019
 */


#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#define PORT 8080

int main(int argc, char const *argv[]) {

		int sockfd, nSocket, valRead;
		struct sockaddr_in addr;
		int opt = 1;
		int addresslen = sizeof(addr);
		char buffer[1024] = {0};
		char *response = "Server responded!";	// Response message from server

		sockfd = socket(AF_INET, SOCK_STREAM, 0);	// File descripter for socket with IPv4 and TCP.

		if(sockfd == 0) {
				perror("socket failed!");
				exit(EXIT_FAILURE);
		}

		// Attach the socket to port 8080 forcefully
		if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
				perror("setsockopt");
				exit(EXIT_FAILURE);
		}

		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY; 	// For localhost
  	addr.sin_port = htons(PORT);

    // Bind the socket to localhost 8080
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening for requests...\n");

		// Wait for client to make approach. Wait for 3.
    if (listen(sockfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Extract the first connection from pending queue and establish connection b/w client and server by creating a new socket.
    if ((nSocket = accept(sockfd, (struct sockaddr *)&addr, (socklen_t*)&addresslen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valRead = read( nSocket , buffer, 1024);
    printf("%s\n",buffer );
    send(nSocket , response , strlen(response) , 0 );
		time_t seconds;
    seconds = time (NULL);
    printf("Response message sent at %ld \n", seconds/3600);
    return 0;
}
