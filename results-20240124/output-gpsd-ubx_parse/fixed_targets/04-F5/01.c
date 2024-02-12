#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

#define kMinInputLength 10
#define kMaxInputLength 9216

extern "C" {
#include <libubox/avl-cmp.h>
#include <libubox/avl.h>
#include <libubox/usock.h>
#include <libubox/uloop.h>
#include <libubox/blobmsg.h>
#include <libubox/blobmsg_json.h>
#include <libubox/utils.h>
#include <libubox/avl-cmp.h>
#include <libubox/avl.h>
#include <libubox/usock.h>
#include <libubox/uloop.h>
#include <libubox/blobmsg.h>
#include <libubox/blobmsg_json.h>
#include <libubox/utils.h>
#include <gpsd/tests/test_packet.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return 0;
    }

    {
        struct gps_device_t device;
        char *ptr = (char*)Data;

        gps_init(&device, NULL, NULL);

        size_t ubx_parse(struct gps_device_t *, char *, size_t);
        size_t st = ubx_parse(&device, ptr, Size);
    }

    return 0;
}