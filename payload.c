#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach-o/dyld.h>

void* foo() {
	while(1) {
		printf("Name: %s\n", _dyld_get_image_name(0));
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
