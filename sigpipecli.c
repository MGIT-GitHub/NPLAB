// // SIG PIPE CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP Address> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd, n, m;
    char buff[100];
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(atoi(argv[2]));

/*    if (inet_pton(AF_INET, argv[1], &serv.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("connect failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("conn done\n");

    // Write to the server first
    m = write(sockfd, "HelloWorld", 10);
    if (m < 0) {
        perror("write failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Read from the server
    while ((n = read(sockfd, buff, sizeof(buff) - 1)) > 0) {
        buff[n] = '\0'; // Ensure null termination
        printf("%s", buff);
    }

    if (n < 0) {
        perror("read failed");
    }

    close(sockfd);
    return 0;
}
