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
    struct gps_lexer_t lexer;

    lexer_init(&lexer, &errout);
    lexer.errout.debug = 0;

    memcpy(lexer.inbufptr = lexer.inbuffer, Data, Size);
    lexer.inbuflen = Size;

    packet_parse(&lexer);

    device.lexer = &lexer;
    tsip_detect(&device);
  }
  {
    struct gpsd_errout_t errout;
    struct gps_device_t device;
    struct gps_lexer_t lexer;
    int nullfd = open("/dev/null", O_RDONLY);
    ssize_t st;

    lexer_init(&lexer, &errout);
    lexer.errout.debug = 0;

    memcpy(lexer.inbufptr = lexer.inbuffer, Data, Size);
    lexer.inbuflen = Size;

    do {
      st = packet_get(nullfd, &lexer);
    } while (st > 0);

    close(nullfd);

    device.lexer = &lexer;
    tsip_detect(&device);
  }

  return 0;
}