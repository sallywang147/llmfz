#include <cstdint>
#include <cstdio>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3)
    return 0;

  const auto count = assign_from_buf<size_t>(data);
  data += sizeof(size_t);
  size -= sizeof(size_t);

  const auto stream = assign_from_buf<FILE *>(data);
  data += sizeof(FILE *);
  size -= sizeof(FILE *);

  if (count > size)
    return 0;

  fmt::detail::fwrite_fully(as_chars(data), count, stream);
  return 0;
}