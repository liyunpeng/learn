#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 1int socket(int family,int type,int protocol)
 13 family:
 14     指定使用的协议簇:AF_INET（IPv4） AF_INET6（IPv6） AF_LOCAL（UNIX协议） AF_ROUTE（路由套接字） AF_KEY（秘钥套接字）
 15 type:
 16     指定使用的套接字的类型:SOCK_STREAM（字节流套接字） SOCK_DGRAM
 17 protocol:
 18     如果套接字类型不是原始套接字，那么这个参数就为0
 19 2、int bind(int sockfd, struct sockaddr *myaddr, int addrlen)
 20 sockfd:
 21     socket函数返回的套接字描述符
 22 myaddr:
 23     是指向本地IP地址的结构体指针
 24 myaddrlen:
 25     结构长度
 26 struct sockaddr{
 27     unsigned short sa_family; //通信协议类型族AF_xx
 28     char sa_data[14];  //14字节协议地址，包含该socket的IP地址和端口号
 29 };
 30 struct sockaddr_in{
 31     short int sin_family; //通信协议类型族
 32     unsigned short int sin_port; //端口号
 33     struct in_addr sin_addr; //IP地址
 34     unsigned char si_zero[8];  //填充0以保持与sockaddr结构的长度相同
 35 };
 36 3、int connect(int sockfd,const struct sockaddr *serv_addr,socklen_t addrlen)
 37 sockfd:
 38     socket函数返回套接字描述符
 39 serv_addr:
 40     服务器IP地址结构指针
 41 addrlen:
 42     结构体指针的长度
 43 4、int listen(int sockfd, int backlog)
 44 sockfd:
 45     socket函数绑定bind后套接字描述符
 46 backlog:
 47     设置可连接客户端的最大连接个数，当有多个客户端向服务器请求时，收到此值的影响。默认值20
 48 5、int accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen)
 49 sockfd:
 50     socket函数经过listen后套接字描述符
 51 cliaddr:
 52     客户端套接字接口地址结构
 53 addrlen:
 54     客户端地址结构长度
 55 6、int send(int sockfd, const void *msg,int len,int flags)
 56 7、int recv(int sockfd, void *buf,int len,unsigned int flags)
 57 sockfd:
 58     socket函数的套接字描述符
 59 msg:
 60     发送数据的指针
 61 buf:
 62     存放接收数据的缓冲区
 63 len:
 64     数据的长度，把flags设置为0
*/
int main(int argc, char *argv[])
{
	int server_sockfd;//服务器端套接字
	int client_sockfd;//客户端套接字
	int len;
	struct sockaddr_in my_addr;   //服务器网络地址结构体
	struct sockaddr_in remote_addr; //客户端网络地址结构体
	int sin_size;
	char buf[BUFSIZ];  //数据传送的缓冲区
	memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零
	my_addr.sin_family=AF_INET; //设置为IP通信
	my_addr.sin_addr.s_addr=INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上
	my_addr.sin_port=htons(8000); //服务器端口号

	/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
	if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket error");
		return 1;
	}


	/*将套接字绑定到服务器的网络地址上*/
	if(bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
	{
		perror("bind error");
		return 1;
	}

	/*监听连接请求--监听队列长度为5*/
	if(listen(server_sockfd,5)<0)
	{
		perror("listen error");
		return 1;
	};

	sin_size=sizeof(struct sockaddr_in);

	/*等待客户端连接请求到达*/
	if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0)
	{
		perror("accept error");
		return 1;
	}
	printf("accept client %s\n",inet_ntoa(remote_addr.sin_addr));
	len=send(client_sockfd,"Welcome to my server\n",21,0); //发送欢迎信息

	/*接收客户端的数据并将其发送给客户端--recv返回接收到的字节数，send返回发送的字节数*/
	while((len=recv(client_sockfd,buf,BUFSIZ,0))>0) //
	{
		//buf[len-1]='/0';
		printf("%s\n",buf);
		if(send(client_sockfd,buf,len,0)<0)
		{
			perror("write error");
			return 1;
		}
	}


	/*关闭套接字*/
	 close(client_sockfd);
	 close(server_sockfd);

	return 0;

}
