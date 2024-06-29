//sockClient
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main(int argc,char *argv[])
{
 int sockfd,len,connfd,n;
 char buff[100];
 struct sockaddr_in serv;
 bzero(&serv,sizeof(serv));
 serv.sin_family=AF_INET;
 serv.sin_port=htons(atoi(argv[1]));
 serv.sin_addr.s_addr=htonl(INADDR_ANY);
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(connect(sockfd,(struct sockaddr *)&serv,sizeof(serv))<0)
 printf("Connection unsuccessfull");
 else
 write(sockfd,"Hello",5);
}
