 #include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) 
{//gpsd/tests//test_packet.c

    if (Size < 10 || Size > 9216){
        return 0;
    }

    {
        struct gps_device_t *device;

        device = gps_open(NULL, NULL, NULL);
        if (device == NULL) {
            return 0;
        }

        gpsd_poll(device);

        gps_close(device);
    }

    return 0;
}