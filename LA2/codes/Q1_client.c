/** @file Q1_client.c
 * @brief Solution of Question 1 of LA2. Code for client.
 *
 *  @author Shashank
 *
 * @date 7/31/2019
 */


#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int Socket = 0, valueread;
    struct sockaddr_in serv_addr;
    char *request = "Client requesting...";
    char buffer[1024] = {0};

    if ((Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(Socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    time_t seconds;
    seconds = time (NULL);
    send(Socket , request , strlen(request) , 0 );
    printf("Request message sent at %ld \n", seconds/3600);
    valueread = read( Socket , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}
