#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // gpsd/tests//test_packet.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  {
    struct gpsd_errout_t errout;
    struct gps_device_t device;
    char buffer[kMaxInputLength];

    device.gpsdata.dev.path = "fuzz";
    device.gpsdata.dev.baudrate = 4800;
    device.gpsdata.dev.flags = 0;
    device.lexer.errout.debug = 0;

    memcpy(buffer, Data, Size);

    ubx_parse(&device, buffer, Size);
  }
  {
    struct gpsd_errout_t errout;
    struct gps_device_t device;
    char buffer[kMaxInputLength];
    int nullfd = open("/dev/null", O_RDONLY);
    ssize_t st;

    device.gpsdata.dev.path = "fuzz";
    device.gpsdata.dev.baudrate = 4800;
    device.gpsdata.dev.flags = 0;
    device.lexer.errout.debug = 0;

    memcpy(buffer, Data, Size);

    do {
      st = ubx_get(&device, nullfd);
    } while (st > 0);

    close(nullfd);
  }

  return 0;
}