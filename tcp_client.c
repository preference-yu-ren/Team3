#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
/*int main()
{
 int sockfd = 0;
 int ret = 0;
 char msg[] = "hello server";
 char buf[64] = {0};
 
 //1.创建ICP3 ocket
 sockfd = socket(AF_INET,SOCK_STREAM,0);
 
 //2.向服务器发起连接
 //res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
 
 //3.发送客户端数据请求
 send(connfd,msg,strlen(msg),O);
 
 //4.接收服务器的数据响应
 //recv(connfd,buf,sizeof(buf),0);
 
 close(sockfd);
 
 return 0;
}*/

int main() 
{ 
 int sockfd; 
    if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0))) 
    { 
        perror("socket"); 
        return -1; 
    } 
    printf("socket...........\n"); 
    struct sockaddr_in srv_addr; 
    memset(&srv_addr, 0, sizeof(srv_addr)); 
    srv_addr.sin_family         = AF_INET; 
    srv_addr.sin_port           = htons(8888); 
    srv_addr.sin_addr.s_addr    = inet_addr("192.168.0.101"); 
    if (0 > connect(sockfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr))) 
    { 
        perror("connect"); 
        return -1; //exit //pthread_exit 
    } 
    printf("connect..............\n"); 
    char msg[] = "hello server"; 
    int ret; 
    //while (1) 
    { 
        //printf("send: "); 
        //fgets(buf, sizeof(buf), stdin); 
        ret = write(sockfd, msg, sizeof(msg)); 
    } 
    close(sockfd); 
    return 0; 

} 