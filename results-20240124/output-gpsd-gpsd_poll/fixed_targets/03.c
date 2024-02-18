#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define GPSD_CONFIG_H
#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
#include "gpsd.h"

#define MAX_DEVICES 128
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 0;
    }

    {
        struct gps_device_t device;
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        gps_init(&device, WATCH_ENABLE | WATCH_JSON);
        device.errout.debug = 0;

        memcpy(device.inbufptr = device.inbuffer, Data, Size);
        device.inbuflen = Size;

        do {
            st = gpsd_poll(&device);
        } while (st > 0);

        close(nullfd);
    }

    return 0;
}
}