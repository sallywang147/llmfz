 #include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpsd.h"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) 
{
    int res;
    struct gps_device_t *dev;
    func_type *func;
    float timeout;

    if (Size < 100)
        return 0;

    dev = gps_open(NULL, NULL, NULL);
    if (dev == NULL)
        return 0;

    res = gpsd_multipoll(false, dev, func, timeout);

    gps_close(dev);

    return res;
}