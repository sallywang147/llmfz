#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

extern "C" {
#include "parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> bytes(data, data + size);
  std::string input(bytes.begin(), bytes.end());
  std::ifstream ifs("/dev/null");
  struct parse *p = parse_new(ifs, 0);
  p_bre(p, 0, 0);
  parse_free(p);
  return 0;
}