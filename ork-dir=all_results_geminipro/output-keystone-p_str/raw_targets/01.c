#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct parse* p = parse_new();
  if (p == NULL) {
    return 0;
  }

  std::vector<uint8_t> input_buffer(data, data + size);
  input_buffer.push_back('\0');
  p->buf = input_buffer.data();
  p->buf_size = size + 1;
  p->buf_ptr = 0;

  p_str(p);

  parse_free(p);

  return 0;
}