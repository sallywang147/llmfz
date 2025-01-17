 #include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "log.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        struct Log log;
        char *format = (void *)data;
        size_t format_len = size;
        struct __va_list_tag args;

        if (size < sizeof(char *))
                return 0;

        log_init(&log);

        va_start(args, format);
        log_vcommitf(&log, format, &args);
        va_end(args);

        log_fini(&log);

        return 0;
}