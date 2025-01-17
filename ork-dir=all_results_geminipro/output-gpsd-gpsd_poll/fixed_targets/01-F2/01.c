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

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <NMEA string>\n", argv[0]);
    return 1;
  }

  struct gps_device_t gps_device;
  if (gpsd_init(&gps_device, NULL) != 0) {
    fprintf(stderr, "gpsd_init() failed\n");
    return 1;
  }

  size_t packet_length = strlen(argv[1]);
  if (packet_length < kMinInputLength || packet_length > kMaxInputLength) {
    fprintf(stderr, "invalid packet length: %zu\n", packet_length);
    return 1;
  }

  gpsd_poll(&gps_device);

  return 0;
}