#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pcre_malloc_init();
    initialized = true;
  }

  std::vector<uint8_t> output_buffer(size);
  struct parse* parse = pcre_study(reinterpret_cast<const char*>(data), 0, &output_buffer[0]);
  if (parse == NULL) {
    return 0;
  }

  int ret = p_simp_re(parse, 0);

  pcre_free_study(parse);

  return ret;
}