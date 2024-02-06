#include <utf8proc.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1)
    return 0;

  /* Avoid timeout with long inputs */
  if (size > (64 * 1024))
    return 0;

  if (data[size - 1] != '\0')
    return 0;

  utf8proc_errmsg(size);

  return 0;
}