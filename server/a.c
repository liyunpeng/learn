#include <sys/socket.h>
#include <net/inet.h>

int main()
{
	struct sockaddr_in sockaddra;
	sockaddra.sin_family=AF_INET;
	sockaddra.sin_port=htons(20);
	sockaddra.sin_addr.sin_addr=20;
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0); 

	bind(socket_fd, &sockaddra, sizeof(sockaddra));

	listen(socket_fd, 10);

	while(1)
	{
		int s = sizeof(sockaddra);
		accept(socket_fd, &client_adddr, &s);
	}
}
