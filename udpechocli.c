#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
int main(int argc,char *argv[])
{
 int sockfd;
 char buff[100];
 struct sockaddr_in serv;
 bzero(&serv,sizeof(serv));
 serv.sin_family=AF_INET;
 serv.sin_port=htons(atoi(argv[1]));
 serv.sin_addr.s_addr=htonl(INADDR_ANY);
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 printf("Enter text:");
 scanf("%s",buff);
 sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&serv,sizeof(serv));
}
