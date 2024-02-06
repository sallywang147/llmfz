#include "gpsd_config.h" /* must be before all includes */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // gpsd/tests//test_packet.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  {
    struct gpsd_errout_t errout;
    struct gps_device_t device;

    device_init(&device, &errout);
    device.errout.debug = 0;

    memcpy(device.inbufptr = device.inbuffer, Data, Size);
    device.inbuflen = Size;

    size_t ret = parse_input(&device);

    device_release(&device);
    return ret;
  }
  {
    struct gpsd_errout_t errout;
    struct gps_device_t device;
    int nullfd = open("/dev/null", O_RDONLY);
    ssize_t st;

    device_init(&device, &errout);
    device.errout.debug = 0;

    memcpy(device.inbufptr = device.inbuffer, Data, Size);
    device.inbuflen = Size;

    do {
      st = packet_get(nullfd, &device);
    } while (st > 0);

    close(nullfd);
    device_release(&device);
  }

  return 0;
}