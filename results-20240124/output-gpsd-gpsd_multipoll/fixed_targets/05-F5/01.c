#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
#include "gpsd/gpsd_json.h"
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // gpsd/tests//test_packet.c

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 0;
    }

    {
        struct gps_device_t device;
        struct gps_lexer_t lexer;
        func_type *func = json_lexer_init(&lexer);
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        lexer_init(&lexer);
        lexer.errout.debug = 0;

        memcpy(lexer.inbufptr = lexer.inbuffer, Data, Size);
        lexer.inbuflen = Size;

        gpsd_multipoll(0, &device, func, 0.0);

        close(nullfd);
    }

    return 0;
}