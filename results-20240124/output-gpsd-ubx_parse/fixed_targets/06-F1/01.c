#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPSD_CONFIG_H

#include "gpsd.h"

extern "C" {
#include "gpsdclient.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    struct gps_device_t device;
    memset(&device, 0, sizeof(device));

    device.gpsdata.dev.path = "fuzz";
    device.gpsdata.dev.baudrate = 9600;
    device.gpsdata.dev.settings.device_type = SERVICE_UNKNOWN;
    device.gpsdata.dev.driver = &gpsd_test_driver;

    size_t ret = ubx_parse(&device, (char *)Data, Size);

    return ret;
}