//TCP CONCURRENT server
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
void main() {
int sockfd,len,connfd,n,m,fd,n1,fd1,pid;
char buff[100],file[15],buff1[100];
struct sockaddr_in serv,cli;
bzero(&serv,sizeof(serv));
serv.sin_family=AF_INET;
serv.sin_port=htons(13552);
serv.sin_addr.s_addr=htonl(INADDR_ANY);
sockfd=socket(AF_INET,SOCK_STREAM,0);
bind(sockfd,(struct sockaddr *)&serv,sizeof(serv));
listen(sockfd,5);
for(;;)
{
 printf("Server running\n");
 len=sizeof(cli);
 connfd=accept(sockfd,(struct sockaddr *)&cli,&len);
 printf("%d\n",connfd);
 printf("Connection established\n");
 pid=fork();
 if(pid==0)
{
  close(sockfd);
  n1=read(connfd,buff,sizeof(buff));
  fd1=open(buff,0);
  m=read(fd1,buff1,sizeof(buff1));
  write(connfd,buff1,m);
}
}
}
