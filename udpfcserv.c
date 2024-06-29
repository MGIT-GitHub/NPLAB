// server lack of. Flow control. Udp
#include <stdio.h>             
#include <sys/un.h>            
#include <unistd.h>        
#include <stdlib.h>            
#include <string.h>            
#include <netinet/in.h>        
#include <sys/socket.h>        

int main() {
    int sockfd, len, n, count = 0;
    char buff[100];
    struct sockaddr_in serv, cli;

    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(15136);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    len = sizeof(cli);

    bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

    while ((n = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&cli, &len)) > 0) {
        printf("Message received\n");
        buff[n] = '\0';
        printf("%s\n", buff);
        count++;
    }

    printf("Total messages received: %d\n", count);

    close(sockfd);

    return 0;
}
