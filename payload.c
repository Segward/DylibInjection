#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void* foo() {
	while(1) {
		void* baseAddress = getBaseAddress();
		printf("Base address: %p\n", baseAddress);
		sleep(1);
	}
}

void* getBaseAddress() {
	const struct mach_header* mh = _dyld_get_image_header(0);
	return (void*)mh;
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
