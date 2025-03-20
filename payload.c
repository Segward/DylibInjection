#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach-o/dyld.h>
#include <libproc.h>
#include <sys/types.h>
#include <sys/sysctl.h>

void* foo() {
	while(1) {
		// Print the PID of the process
		pid_t pid = getpid();
		printf("PID: %d\n", pid);
		
		// Print the path of the executable
		char path[1024];
		int length = proc_pidpath(pid, path, sizeof(path));
		printf("Path: %s\n", path);
		sleep(1);
	}
}

__attribute((constructor))
void init() {
	// Create a thread
	pthread_t thread;
	if (pthread_create(&thread, NULL, foo, NULL) != 0) {
		printf("Error creating thread\n");
		exit(1);
	}
	
	// Detach the thread
	pthread_detach(thread);	
}
