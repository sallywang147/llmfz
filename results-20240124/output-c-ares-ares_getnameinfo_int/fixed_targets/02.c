#include <ares.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <ares_version.h>
}

int main(int argc, char **argv) {
  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    fprintf(stderr, "ares_init() failed: %s\n", ares_strerror(status));
    return EXIT_FAILURE;
  }

  char *name = NULL;
  status = ares_getnameinfo_int(channel, "www.google.com", 0,
                                ARES_NI_NO_PORT, &name);
  if (status != ARES_SUCCESS) {
    fprintf(stderr, "ares_getnameinfo_int() failed: %s\n", ares_strerror(status));
    ares_destroy(channel);
    return EXIT_FAILURE;
  }

  printf("Name: %s\n", name);

  ares_free_string(name);
  ares_destroy(channel);
  return EXIT_SUCCESS;
}