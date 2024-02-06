#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct parse* p = parse_new();
  if (p == nullptr) {
    return 0;
  }

  std::vector<uint8_t> input(data, data + size);
  input.push_back('\n');
  parse_buffer(p, input.data(), input.size());
  nonnewline(p);
  parse_free(p);

  return 0;
}