#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        struct Log log;
        char *format = (void *)data;
        int r;

        if (size < sizeof(char *))
                return 0;

        memcpy(&log, data + sizeof(char *), sizeof(log));

        r = log_vcommitf(&log, format, (struct __va_list_tag *)(data + sizeof(char *) + sizeof(log)));
        if (r)
                return 0;

        return 0;
}