#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libfuzzer/libfuzzer_macro.h"
#ifdef __cplusplus
}
#endif

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  FuzzedDataProvider stream(data, size);
  int err = stream.ConsumeIntegralInRange<int>(0, 100000);

  const char * description = http_errno_description((http_errno)err);
  if (description != NULL)
    free((void*)description);

  return 0;
}