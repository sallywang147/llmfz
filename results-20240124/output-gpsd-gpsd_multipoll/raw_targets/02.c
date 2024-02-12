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
        func_type func;
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        device.gpsdata.dev.baudrate = 4800;

        gpsd_multipoll(false, &device, &func, 0.0);

        do {
            st = packet_get(nullfd, &device.lexer);
        } while (st > 0);

        close(nullfd);
    }

    return 0;
}