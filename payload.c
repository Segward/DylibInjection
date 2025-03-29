#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <mach-o/dyld.h>

void* foo() {
  const char* name = _dyld_get_image_name(1);
  if (strstr(name, "Player") == NULL) {
    return NULL;
  }

  const struct mach_header* header = _dyld_get_image_header(1);
  if (header == NULL) {
    return NULL;
  }

  uintptr_t offset = 0x1b255c;
  uintptr_t print = (uintptr_t)header + offset;
  void (*func)(int, const char*) = (void (*)(int, const char*))print;
  
  while (1) {
    func(0, "Hello from injected code\n");
    sleep(1);
  }

  return NULL;
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
