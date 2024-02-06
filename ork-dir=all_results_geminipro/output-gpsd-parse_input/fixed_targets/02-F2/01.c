#include "gpsd_config.h" /* must be before all includes */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
#include "gpsd/tests/test_packet.c"
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <input file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Open the input file
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("open");
    return EXIT_FAILURE;
  }

  // Read the input file into a buffer
  char *input = malloc(kMaxInputLength);
  if (input == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
  }
  size_t input_length = read(fd, input, kMaxInputLength);
  if (input_length == -1) {
    perror("read");
    return EXIT_FAILURE;
  }

  // Close the input file
  close(fd);

  // Create a GPS device struct
  struct gps_device_t device;
  gpsd_init(&device, NULL);

  // Parse the input data
  size_t parsed_length = parse_input(&device, input, input_length);

  // Print the parsed data
  printf("Parsed %zu bytes of data\n", parsed_length);

  // Free the input buffer
  free(input);

  return EXIT_SUCCESS;
}