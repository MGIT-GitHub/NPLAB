// // SIG PIPE SERVER
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>

void sig_handler(int signo) {
    int pid, stat;
    pid = wait(&stat);
    printf("%d terminated child \n", pid);
}

int main() {
    int sockfd, connfd, n;
    char buff[100];
    struct sockaddr_in serv, cli;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(15117);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    signal(SIGCHLD, sig_handler);

    printf("server is running with pid = %d\n", getpid());

    for (;;) {
        len = sizeof(cli);
        connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
        if (connfd < 0) {
            perror("accept failed");
            continue;
        }

        printf("conn done\n");
        int pid = fork();
        if (pid == 0) { // Child process
            close(sockfd);
            while ((n = read(connfd, buff, sizeof(buff))) > 0) {
                buff[n] = '\0'; // Ensure null-termination
                printf("Received: %s\n", buff); // Print the received message
                write(connfd, buff, n);
            }

            if (n < 0) {
                perror("read failed");
            } else if (n == 0) {
                printf("Client disconnected\n");
            }

            close(connfd);
            exit(0);
        } else if (pid > 0) { // Parent process
            close(connfd);
        } else {
            perror("fork failed");
            close(connfd);
        }
    }

    close(sockfd);
    return 0;
}
