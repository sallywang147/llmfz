#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        struct Log *log = (void *)data;
        struct __va_list_tag *args = (void *)(data + sizeof(struct Log));

        log_commit_stderr(log, (char *)(data + sizeof(struct Log) + sizeof(struct __va_list_tag)), args);

        return 0;
}