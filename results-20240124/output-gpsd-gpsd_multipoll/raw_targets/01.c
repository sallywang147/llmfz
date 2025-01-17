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
        device.gpsdata.set = 0;
        gpsd_multipoll(true, &device, NULL, 0);
    }
    {
        struct gps_device_t device;
        device.gpsdata.set = 0;
        gpsd_multipoll(false, &device, NULL, 0);
    }
    {
        struct gps_device_t device;
        device.gpsdata.set = 0;
        gpsd_multipoll(true, &device, NULL, 1);
    }
    {
        struct gps_device_t device;
        device.gpsdata.set = 0;
        gpsd_multipoll(false, &device, NULL, 1);
    }

    return 0;
}