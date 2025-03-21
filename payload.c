#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>

void taskForPid(pid_t pid, task_t *task) {
	if (pid == -1) {
		printf("Error: Invalid PID\n");
		exit(1);
	}

	if (task_for_pid(mach_task_self(), pid, task) != KERN_SUCCESS) {
		printf("Error: Unable to get task for PID %d. Are you running as root?\n", pid);
		exit(1);
	}
}

void debugFirstPage(task_t task) {
	mach_vm_address_t address = 0;
	mach_vm_size_t size = 0;
	vm_region_basic_info_data_64_t info;
	mach_msg_type_number_t info_count = VM_REGION_BASIC_INFO_COUNT_64;
	memory_object_name_t object;

	kern_return_t kr = mach_vm_region(task, &address, &size, 
		VM_REGION_BASIC_INFO, (vm_region_info_t)&info, &info_count, &object);

	if (kr != KERN_SUCCESS) {
		printf("Error: Unable to get first page\n");
		exit(1);
	}

	printf("Address: %p | Size: %llu | Protection: %x\n", 
		(void*)address, (unsigned long long)size, info.protection);

}


void* foo() {
    while (1) {
        pid_t pid = getpid();
		task_t task;
		taskForPid(pid, &task);
		debugFirstPage(task);
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