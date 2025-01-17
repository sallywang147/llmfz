 #include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 0;
    }

    {
        struct gps_device_t device;
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        device_init(&device);
        device.gpsdata.dev.path = "/dev/null";
        device.gpsdata.dev.baudrate = 9600;
        device.gpsdata.dev.settings.device_type = DEVICE_TYPE_SERIAL;

        do {
            st = gpsd_multipoll(false, &device, NULL, 0.1);
        } while (st > 0);

        close(nullfd);
    }

    return 0;
}