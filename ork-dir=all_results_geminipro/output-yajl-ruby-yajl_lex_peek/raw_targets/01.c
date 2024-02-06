#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "yajl/yajl_lex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    yajl_config(yajl_allow_comments, 1);
    initialized = true;
  }
  yajl_lexer_t* lexer = yajl_alloc_lexer(nullptr);
  if (lexer == nullptr) {
    return 0;
  }

  std::vector<uint8_t> json_buffer(size);
  memcpy(json_buffer.data(), data, size);
  const char* json_text = reinterpret_cast<char*>(json_buffer.data());
  int ret = yajl_lex_peek(lexer, json_text, size, 0);
  if (ret == yajl_lex_error) {
    yajl_free_lexer(lexer);
    return 0;
  }

  yajl_free_lexer(lexer);
  return 0;
}