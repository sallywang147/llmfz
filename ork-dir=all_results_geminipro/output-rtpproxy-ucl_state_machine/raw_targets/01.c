#include <fuzzer/FuzzedDataProvider.h>
#include <ucl/ucl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }
  size_t consumed = 0;
  while (consumed < size) {
    size_t next_size = provider.ConsumeIntegralInRange<size_t>(0, size - consumed);
    if (next_size == 0) {
      break;
    }
    auto next_input = provider.ConsumeBytes<char>(next_size);
    ucl_parser_add(parser, next_input.data(), next_input.size());
    consumed += next_size;
  }
  bool ret = ucl_state_machine(parser);
  ucl_parser_free(parser);
  return 0;
}