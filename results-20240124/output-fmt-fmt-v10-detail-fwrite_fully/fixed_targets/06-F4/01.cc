#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "fuzzer-common.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static_assert(sizeof(FILE*) <= fixed_size, "fixed size is too small");
  if (size <= fixed_size + 1) return 0;

  FILE* stream = assign_from_buf<FILE*>(data);
  data += fixed_size;
  size -= fixed_size;

  // data is already allocated separately in libFuzzer so reading past the end
  // will most likely be detected anyway.
  const auto buf = std::string_view(as_chars(data), size);

  // Write in chunks of 100 bytes.
  for (size_t i = 0; i < buf.size(); i += 100) {
    fwrite(const_cast<char*>(buf.data() + i),
                              std::min(buf.size() - i, static_cast<size_t>(100u)), 1, stream);
  }

  return 0;
}