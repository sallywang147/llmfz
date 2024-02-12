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
        struct gps_lexer_t lexer;
        int nullfd = open("/dev/null", O_RDONLY);
        ssize_t st;

        memset(&device, 0, sizeof(device));
        lexer_init(&lexer, NULL);
        lexer.errout.debug = 0;
        device.lexer = &lexer;

        memcpy(lexer.inbufptr = lexer.inbuffer, Data, Size);
        lexer.inbuflen = Size;

        do {
            st = packet_get(nullfd, &lexer);
        } while (st > 0);

        close(nullfd);

        size_t result = parse_input(&device);
        if (result == 0) {
            return 0;
        }
    }

    return 0;
}