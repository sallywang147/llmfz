#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <ucl.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new parser object
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Feed data to the parser
  std::string str = stream.ConsumeRemainingBytesAsString();
  ucl_parser_add_chunk(parser, reinterpret_cast<const unsigned char *>(str.c_str()), str.size());

  // Call the target function
  bool result = ucl_state_machine(parser);

  // Cleanup
  ucl_parser_free(parser);

  return 0;
}