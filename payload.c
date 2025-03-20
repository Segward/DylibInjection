#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void* foo() {
	while(1) {
		printf("Payload running\n");
		sleep(1);
	}
}

__attribute((constructor))
void init() {
	pthread_t thread;
	
	if (pthread_create(&thread, NULL, foo, NULL) != 0) {
		printf("Error creating thread\n");
		exit(1);
	}

	pthread_detach(thread);	
}
