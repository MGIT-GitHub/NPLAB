#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
void main() {
int sockfd,len;
char buff[100];
struct sockaddr_in serv,cli;
bzero(&serv,sizeof(serv));
serv.sin_family=AF_INET;
serv.sin_port=htons(15136);
serv.sin_addr.s_addr=htonl(INADDR_ANY);
sockfd=socket(AF_INET,SOCK_DGRAM,0);
bind(sockfd,(struct sockaddr *)&serv,sizeof(serv));
listen(sockfd,5);
for(;;)
{
printf("Server running\n");
len=sizeof(cli);
recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&cli,&len);
printf("%s",buff);
}
}
