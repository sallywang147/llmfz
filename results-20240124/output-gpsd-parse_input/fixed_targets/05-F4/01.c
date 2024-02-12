#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
#include <gps.h>
#include <stdbool.h>
#include <stddef.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 0;
    }

    {
        struct gps_device_t device;

        device.lexer.errout.debug = 0;

        memcpy(device.lexer.inbufptr = device.lexer.inbuffer, Data, Size);
        device.lexer.inbuflen = Size;

        parse_input(&device);
    }

    return 0;
}