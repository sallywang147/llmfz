#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

extern "C" {
#include "gpsdclient.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) 
{//gpsd/tests//test_packet.c

    if (Size < 1 || Size > 9216){
        return 0;
    }

    {
        struct gps_device_t dev;

        device_init(&dev, "fuzzer");
        dev.lexer.errout.debug = 0;

        memcpy(dev.lexer.inbufptr = dev.lexer.inbuffer, Data, Size);
        dev.lexer.inbuflen = Size;

        bool ret = tsip_detect(&dev);
    }

    return 0;
}