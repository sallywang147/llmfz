#include "gpsd_config.h" /* must be before all includes */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
#include "gpsd/tests//test_packet.c"
}

int main(int argc, char **argv) {
  struct gps_device_t gps_device;
  size_t parse_input_result = parse_input(&gps_device);
  return LLVMFuzzerTestOneInput((const uint8_t *)argv[1], strlen(argv[1]));
}