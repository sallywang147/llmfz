#include <errno.h>
#include <syslog.h>

#include "compressor.h"
#include "fuzz.h"
#include "log.h"
#include "util.h"

extern "C" {
#include "header.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        _cleanup_free_ void *buf = NULL;
        int r;

        if (size < offsetof(struct header, data) + 1)
                return 0;

        /* We don't want to fill the logs with messages about parse errors.
         * Disable most logging if not running standalone */
        if (!getenv("CASYNC_LOG_LEVEL"))
                set_log_level(LOG_CRIT);

        const struct header *h = (struct header*) data;
        const size_t data_len = size - offsetof(struct header, data);

        _cleanup_(compressor_finish) CompressorContext c = COMPRESSOR_CONTEXT_INIT;

        r = compressor_start_encode(&c, h->alg);
        if (r < 0) {
                log_debug_errno(r, "compressor_start_encode failed: %m");
                return 0;
        }

        log_info("Using compression %d, data size=%zu", h->alg, data_len);

        size_t out_size = MAX(size, 128u), /* Make the buffer a bit larger for very small data */
                ret_done;
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

        return 0;
}