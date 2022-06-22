#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
/*int main()
{
 int sockfd = 0;
    char buf[64] = {0};
	char msg[] = "hello client"
	//1.创建TCP socket
	sockfd = socket (AF_INET,SOCK_STREAM,0);
 
	//2.绑定IP地址与端口号
	//bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen)
	
	//3.创建监听客户端连接队列
	//listen(sockfd,10);
 
	//4.等待并建立客户端的连接
	connfd = accept(sockfd,const struct sockaddr *addr,socklen_t addrlen);
	
	//5.接收客户端情求
	//recv(connfd,buf,sizeof(buf),0);
	
	//6.发送服务器响应
	send(connfd,msg,strlen(msg),0);
 
	close(sockfd);
	close(connfd);
 return 0;
}*/

#include <stdio.h> 

#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main() 

{ 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);//创建套接字 
    if (sockfd < 0) 
    { 
        perror("socket"); 
        return -1; 
    } //创建失败的错误处理 
    printf("socket..............\n"); //成功则打印“socket。。。。” 
 
    struct sockaddr_in myaddr; //创建“我的地址”结构体 
    memset(&myaddr, 0, sizeof(myaddr)); //对内存清零（保险起见） 
    myaddr.sin_family       = AF_INET; //选择IPV4地址类型 
    myaddr.sin_port         = htons(8888); //选择端口号 
    myaddr.sin_addr.s_addr  = inet_addr("192.168.0.102"); //选择IP地址 

 if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))//绑定套接字 
    { 
        perror("bind"); 
        return -1; 
    } 
    printf("bind..........\n"); 

    if (0 > listen(sockfd, 8))//调用listen对指定端口进行监听 
    { 
        perror("listen"); 
        return -1; 
    } 
    printf("listen............\n"); 

    int connfd = accept(sockfd, NULL, NULL);//使用accept从消息队列中获取请求 
    if (connfd < 0) 
    { 
        perror("accept"); 
        return -1; 
    } 
    printf("accept..............\n"); 

    char buf[100];//定义一个数组用来存储接收到的数据 
    int ret; 
    while (1) 
    { 
        memset(buf, 0, sizeof(buf)); 
        ret = read(connfd, buf, sizeof(buf)); 
        if (0 > ret) 
        { 
            perror("read"); 
            break; 
        }//执行while循环读取数据，当 
        else if (0 == ret) 
        { 
            printf("write close!\n"); 
            break; 
        } 
        printf("recv: "); 
        fputs(buf, stdout);//打印接收到的数据 
    } 
    close(sockfd);//关闭套接字 
    close(connfd);//断开连接 
    return 0; 

}