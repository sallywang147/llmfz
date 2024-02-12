#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    //gpsd/tests//test_packet.c

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 0;
    }

    {
        struct gps_lexer_t lexer;

        lexer_init(&lexer, NULL);
        lexer.errout.debug = 0;

        memcpy(lexer.inbufptr = lexer.inbuffer, Data, Size);
        lexer.inbuflen = Size;

        ubx_parse(NULL, lexer.inbuffer, Size);
    }
    {
        struct gps_lexer_t lexer;
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        lexer_init(&lexer, NULL);
        lexer.errout.debug = 0;

        memcpy(lexer.inbufptr = lexer.inbuffer, Data, Size);
        lexer.inbuflen = Size;

        do {
            st = packet_get(nullfd, &lexer);
        } while (st > 0);

        close(nullfd);
    }

    return 0;
}
}