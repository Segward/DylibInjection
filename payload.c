#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach-o/dyld.h>

void* foo() {
  // Get the numer of images
  uint32_t count = _dyld_image_count();
  printf("Number of images: %d\n", count);

  // Print the image names
  for (uint32_t i = 0; i < count; i++) {
    const char* name = _dyld_get_image_name(i);
    printf("Image %d: %s\n", i, name);
  }

  // Print the image header
  for (uint32_t i = 0; i < count; i++) {
    const struct mach_header* header = _dyld_get_image_header(i);
    printf("Image %d: %p\n", i, header);
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
