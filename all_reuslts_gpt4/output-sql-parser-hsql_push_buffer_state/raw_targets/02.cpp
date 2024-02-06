#include "fuzzer/FuzzedDataProvider.h"
#include "parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *yyscanner;
  hsql_lex_init(&yyscanner);
  struct yy_buffer_state *buffer = hsql__scan_string(str.c_str(), yyscanner);
  hsql_push_buffer_state(buffer, yyscanner);
  hsql_lex_destroy(yyscanner);

  return 0;
}