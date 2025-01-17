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
        struct gps_device_t device;
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        device_init(&device);

        memcpy(device.lexer.inbufptr = device.lexer.inbuffer, Data, Size);
        device.lexer.inbuflen = Size;

        do {
            st = gpsd_poll(&device);
        } while (st > 0);

        close(nullfd);
    }

    return 0;
}