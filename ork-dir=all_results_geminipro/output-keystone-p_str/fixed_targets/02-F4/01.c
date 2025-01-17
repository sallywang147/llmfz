#include "parser.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct parse *p = parse_new();
  if (p == NULL) {
    return 0;
  }

  std::vector<uint8_t> input_buffer(data, data + size);
  std::string input_string(input_buffer.begin(), input_buffer.end());

  parse_string(p, input_string.c_str());
  p_str(p);
  parse_free(p);
  return 0;
}