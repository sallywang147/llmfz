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
        char *buffer = (char *)malloc(Size + 1);

        device_init(&device, NULL, NULL);
        memcpy(buffer, Data, Size);
        buffer[Size] = '\0';
        ubx_parse(&device, buffer, Size);
        free(buffer);
    }

    return 0;
}