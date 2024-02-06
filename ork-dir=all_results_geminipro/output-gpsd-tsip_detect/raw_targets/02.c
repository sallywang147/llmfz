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
    struct gps_device_t dev;

    lexer_init(&dev.lexer, &errout);
    dev.lexer.errout.debug = 0;

    memcpy(dev.lexer.inbufptr = dev.lexer.inbuffer, Data, Size);
    dev.lexer.inbuflen = Size;

    tsip_detect(&dev);
  }
  {
    struct gpsd_errout_t errout;
    struct gps_device_t dev;
    int nullfd = open("/dev/null", O_RDONLY);
    ssize_t st;

    lexer_init(&dev.lexer, &errout);
    dev.lexer.errout.debug = 0;

    memcpy(dev.lexer.inbufptr = dev.lexer.inbuffer, Data, Size);
    dev.lexer.inbuflen = Size;

    do {
      st = packet_get(nullfd, &dev.lexer);
    } while (st > 0);

    close(nullfd);
  }

  return 0;
}