#include <pthread.h>
#include <stdio.h>
void *thread_func(void *arg)
{
	// why it not print
	printf("thread a started... \n");
	return ( (void *) 0);
}
	pthread_t p;
void start_threada()
{
	
	int result;
	result = pthread_create(&p, NULL, thread_func, NULL);
	if (result == 0 ){
		printf("thread create successfully. \n ");
	} else {
		printf("thread create failed. \n " );
	}
}
