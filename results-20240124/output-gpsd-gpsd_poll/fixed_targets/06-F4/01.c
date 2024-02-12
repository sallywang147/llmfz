#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm> // Fix the missing header file

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

extern "C" {
#include "gpsd.h"
}

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{//gpsd/tests//test_packet.c

    if (Size < kMinInputLength || Size > kMaxInputLength){
        return 0;
    }

    {
        struct gps_device_t dev;

        gpsd_init(&dev, NULL);
        gpsd_poll(&dev);
        gpsd_close(&dev);
    }
    {
        struct gps_device_t dev;
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        gpsd_init(&dev, NULL);
        gpsd_set_raw(&dev, nullfd);

        memcpy(dev.inbuffer, Data, Size);
        dev.inbuflen = Size;

        do {
            st = gpsd_poll(&dev);
        } while (st > 0);

        close(nullfd);
    }

    return 0;
}