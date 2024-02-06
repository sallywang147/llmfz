#include <errno.h>
#include <syslog.h>

#include "compressor.h"
#include "fuzz.h"
#include "log.h"
#include "util.h"

extern "C" {
#include <stdlib.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  _cleanup_free_ void *buf = NULL;
  int r;

  /* We don't want to fill the logs with messages about parse errors.
   * Disable most logging if not running standalone */
  if (!getenv("CASYNC_LOG_LEVEL"))
    set_log_level(LOG_CRIT);

  _cleanup_(compressor_finish) CompressorContext c = COMPRESSOR_CONTEXT_INIT;

  r = compressor_start_encode(&c, 0);
  if (r < 0) {
    log_debug_errno(r, "compressor_start_encode failed: %m");
    return 0;
  }

  log_info("Using compression %d, data size=%zu", 0, size);

  size_t out_size = MAX(size, 128u), /* Make the buffer a bit larger for very small data */
      ret_done;
  buf = malloc(out_size);
  if (!buf) {
    log_oom();
    return 0;
  }

  r = compressor_input(&c, data, size);
  if (r < 0) {
    log_debug_errno(r, "compressor_input failed: %m");
    return 0;
  }

  r = compressor_finish(&c, buf, out_size, &ret_done);
  if (r < 0) {
    log_debug_errno(r, "compressor_finish failed: %m");
    return 0;
  }

  return 0;
}
```

The issue was that the `log.h` header was not wrapped with `extern "C" {}` which is required for the object linking to succeed.

The fix is to wrap the `#include "log.h"` directive with `extern "C" {}` like this:

```c++
extern "C" {
#include "log.h"
}