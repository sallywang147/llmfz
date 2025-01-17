#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <dropbear/dropbear.h>
#include <dropbear/ssh.h>
#include <dropbear/dbutil.h>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  dropbear_exit = exit;
  svr_ensure_hostkey();
  dropbear_log(LOG_WARNING, "Got %d bytes of input", (int)size);
  dropbear_log(LOG_WARNING, "Input: %s", data);
}