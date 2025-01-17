#include <errno.h>
#include <syslog.h>

#include "compressor.h"
#include "fuzz.h"
#include "log.h"
#include "util.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        _cleanup_(compressor_finish) CompressorContext c = COMPRESSOR_CONTEXT_INIT;
        int r;

        /* We don't want to fill the logs with messages about parse errors.
         * Disable most logging if not running standalone */
        if (!getenv("CASYNC_LOG_LEVEL"))
                set_log_level(LOG_CRIT);

        /* We don't want to fuzz the compression algorithm, just the data */
        r = compressor_start_encode(&c, COMPRESSOR_MORE);
        if (r < 0) {
                log_debug_errno(r, "compressor_start_encode failed: %m");
                return 0;
        }

        r = compressor_input(&c, data, size);
        if (r < 0) {
                log_debug_errno(r, "compressor_input failed: %m");
                return 0;
        }

        return 0;
}