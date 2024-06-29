//concurrent client
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
 int sockfd,len,connfd,n;
 char buff[100],file[15];
 struct sockaddr_in serv;
 bzero(&serv,sizeof(serv));
 serv.sin_family=AF_INET;
 serv.sin_port=htons(atoi(argv[1]));
 serv.sin_addr.s_addr=htonl(INADDR_ANY);
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(connect(sockfd,(struct sckaddr *)&serv,sizeof(serv))<0)
 printf("Connection unsuccessfull");
 else {
 printf("Enter a filename:");
 scanf("%s",file);
 write(sockfd,file,sizeof(file));
 n=read(sockfd,buff,sizeof(buff));
 buff[n]='\0';
 write(1,buff,n);
}
}
