#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include </home/liyunpeng/learn/c_api/threada.h>
#include <stdarg.h>
#include <string.h>

void var_multi(const char* p, ...)
{
	char *p1 = 0;

	// last fixed para
	printf("%s\n", p);

	va_list p_list;
	va_start(p_list, p);

	// second variable para
	p1 = va_arg(p_list, char*);
	printf("%s\n", p1);
	
	// third variable para
	p1 = va_arg(p_list, char*);
	printf("%s\n", p1);


	va_end(p_list);
		
}

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
		var_multi("para1", "para2", "para3");
   	}
}


	
