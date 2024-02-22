#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
int parse_input(struct gps_device_t *device);
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) 
{//gpsd/tests//test_packet.c

    if (Size < kMinInputLength || Size > kMaxInputLength){
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