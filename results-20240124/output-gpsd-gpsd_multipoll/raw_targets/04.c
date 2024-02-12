 #include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    struct gps_device_t *device;
    int fd;
    char buf[BUFSIZ];
    ssize_t len;
    int ret;

    device = gpsd_open(NULL, NULL, NULL);
    if (!device) {
        return 0;
    }

    fd = gpsd_fileno(device);
    if (fd < 0) {
        gpsd_close(device);
        return 0;
    }

    if (Size > 0) {
        len = write(fd, Data, Size);
        if (len < 0) {
            gpsd_close(device);
            return 0;
        }
    }

    len = read(fd, buf, sizeof(buf));
    if (len < 0) {
        gpsd_close(device);
        return 0;
    }

    ret = gpsd_multipoll(false, device, NULL, 0.0);

    gpsd_close(device);

    return ret;
}