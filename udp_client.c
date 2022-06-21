#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 5000
int main()
{
	int sock =0;
	struct sockaddr_in addr;//服务器的网路地址
	int addrlen=sizeof(addr);
	char msg[64]={0};
	char buf[64]={0};
	//1.创建UDP socket
	sock = socket (AF_INET,SOCK_DGRAM,0);
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port=htons(SERVER_PORT);//服务器的端口
	addr.sin_addr.s_addr=inet_addr("192.168.0.103");//服务器IP
	//addr.sin_addr.s_addr=inet_addr("127.0.0.1");//内部循环 服务器IP
		
	while(1){
		
		memset(msg, 0, sizeof(msg));
		memset(buf, 0, sizeof(buf));
		//从控制台输入聊天信息
		printf("输入向服务器发送的消息:\n");
		scanf("%s",msg);
		
		//2.发送客户端请求
		sendto(sock,msg,strlen(msg),0,(struct sockaddr *)&addr, addrlen);
	
		//3.接收服务器应答
		recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&addr, &addrlen);
		printf("服务器应答:%s\n",buf);
	}
	
	return 0;
	

}