//client lack of flow. Control udp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
        

    int sockfd, n;
    struct sockaddr_in servaddr;
    char buff[100];
    char ch;

    
    bzero(&servaddr, sizeof(servaddr));

    
    servaddr.sin_family = AF_INET;

    
    servaddr.sin_port = htons(atoi(argv[1]));

    
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    

    // Loop to send messages until EOF (Ctrl+D)
    do {
        printf("Enter message to send (Ctrl+D to exit): ");

        // Read input character by character until newline or EOF
        int i = 0;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            buff[i++] = ch;
        }
        buff[i] = '\0';  //

        // Send message to server
        sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        
    } while (ch != EOF);

    // Close the socket
    close(sockfd);

    return 0;
}
