#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "api/yajl_lex.h"
#include "api/yajl_parse.h"
#include "fuzzer/FuzzedDataProvider.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  yajl_parser_config cfg = {
      .allowComments = 1,
      .checkUTF8 = 1,
  };
  yajl_handle parser = yajl_alloc(NULL, &cfg, NULL, NULL);
  yajl_lexer lexer = yajl_lex_alloc(&cfg, 1, 0);

  std::string jsonText = stream.ConsumeRandomLengthString();
  int jsonTextLen = jsonText.size();
  int offset = stream.ConsumeIntegralInRange<int>(0, jsonTextLen);

  yajl_lex_peek(lexer, jsonText.c_str(), jsonTextLen, offset);

  yajl_lex_free(lexer);
  yajl_free(parser);

  return 0;
}