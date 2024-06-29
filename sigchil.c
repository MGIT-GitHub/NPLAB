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
    int sockfd, connfd, n1, n2, fd;
    char buff[100];
    struct sockaddr_in serv, cli;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(15112);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

   bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    listen(sockfd, 5);

    signal(SIGCHLD, sig_handler);

    for (;;) {
    printf("Server running");
        len = sizeof(cli);
        connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
        
        printf("conn done\n");
        int pid = fork();
        if (pid == 0) { // Child process
            close(sockfd);
            printf("I am inner child with pid = %d\n", getpid());
            n1 = read(connfd, buff, sizeof(buff) - 1);
            buff[n1] = '\0';

            fd = open(buff, O_RDONLY);

            n2 = read(fd, buff, sizeof(buff));
            close(fd);
            write(connfd, buff, n2);
            close(connfd);
            exit(0);
        }
        if (pid > 0) { // Parent process
            close(connfd);
        }
    }

    close(sockfd);
    return 0;
}
