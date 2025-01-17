#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

extern "C" {
#include "gpsd/tests/test_packet.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) 
{

    if (Size < 10 || Size > 9216){
        return 0;
    }

    {
        struct gps_device_t device;

        device.lexer.errout.debug = 0;

        memcpy(device.lexer.inbufptr = device.lexer.inbuffer, Data, Size);
        device.lexer.inbuflen = Size;

        tsip_detect(&device);
    }

    return 0;
}