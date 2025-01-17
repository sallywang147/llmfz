#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // gpsd/tests//test_packet.c

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 0;
    }

    {
        struct gps_device_t device;
        device_init(&device);

        device.gpsdata.dev.fd = open("/dev/null", O_RDONLY);
        device.lexer.inbufptr = device.lexer.inbuffer;
        device.lexer.inbuflen = Size;
        memcpy(device.lexer.inbufptr = device.lexer.inbuffer, Data, Size);

        gpsd_poll(&device);

        close(device.gpsdata.dev.fd);
    }

    return 0;
}