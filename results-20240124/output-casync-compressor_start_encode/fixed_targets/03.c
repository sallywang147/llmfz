#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

extern "C" {
#include "compressor.h"
#include "fuzz.h"
#include "log.h"
#include "util.h"
}

typedef struct header {
        uint32_t alg;
        uint32_t reserved[5]; /* Extra space to keep fuzz cases stable in case we need to
                               * add stuff in the future. */
        uint8_t data[];
} header;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        void *buf = NULL;
        int r;

        if (size < offsetof(header, data) + 1)
                return 0;

        /* We don't want to fill the logs with messages about parse errors.
         * Disable most logging if not running standalone */
        if (!getenv("CASYNC_LOG_LEVEL"))
                set_log_level(LOG_CRIT);

        const header *h = (struct header*) data;
        const size_t data_len = size - offsetof(header, data);

        CompressorContext c = COMPRESSOR_CONTEXT_INIT;

        r = compressor_start_encode(&c, h->alg);
        if (r < 0) {
                log_debug_errno(r, "compressor_start_encode failed: %m");
                return 0;
        }

        log_info("Using compression %d, data size=%zu", h->alg, data_len);

        size_t out_size = MAX(size, 128u); /* Make the buffer a bit larger for very small data */

        buf = malloc(out_size);
        if (!buf) {
                log_oom();
                return 0;
        }

        r = compressor_input(&c, h->data, data_len);
        if (r < 0) {
                log_debug_errno(r, "compressor_input failed: %m");
                return 0;
        }

        r = compressor_finish(&c, buf);
        if (r < 0) {
                log_debug_errno(r, "compressor_finish failed: %m");
                return 0;
        }

        free(buf);
        return 0;
}