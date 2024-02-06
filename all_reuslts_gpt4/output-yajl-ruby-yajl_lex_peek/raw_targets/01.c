#include <fuzzer/FuzzedDataProvider.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "api/yajl_lex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string jsonText = stream.ConsumeRandomLengthString();
  int jsonTextLen = jsonText.length();
  int offset = stream.ConsumeIntegralInRange<int>(0, jsonTextLen);
  yajl_alloc_funcs afs;

  yajl_lexer_t *lexer = yajl_lex_alloc(&afs, NULL, 1, 0);
  assert(lexer != NULL);

  yajl_lex_peek(lexer, (char *)jsonText.c_str(), jsonTextLen, offset);

  yajl_lex_free(lexer);

  return 0;
}