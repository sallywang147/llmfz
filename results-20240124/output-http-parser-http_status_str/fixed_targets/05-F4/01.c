#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <http_parser.h>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int status = stream.ConsumeIntegral<int>();
  const char *s = http_status_str((enum http_status)status);
  free((void *)s);

  return 0;
}