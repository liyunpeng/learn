#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include </home/liyunpeng/learn/c_api/threada.h>

int main()
{
	pid_t pid = fork();
	if( pid == 0 ) {
		printf("sub process beging... \n ");
		char *v[] = {"ls", "-l", NULL};
		char *e[] = {"PATH=/bin/ls", NULL};
		execve("/bin/ls", v, e);
		// why it doesn't print
		printf("sub process end. " );

	} else if ( pid != 0 ) {
		printf("parent process begin...\n " ); 
		waitpid(pid, NULL, 0); 
		printf("parent process receive msg that sub process exit. \n" ); 
		start_threada();
   	}
}


	
