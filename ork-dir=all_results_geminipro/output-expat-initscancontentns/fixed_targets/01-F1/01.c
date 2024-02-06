#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" {
#include "libxml/parserInternals.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);

  // Consume bytes to use as the encoding name.
  std::string encoding_name = stream.ConsumeBytesAsString(16);
  // Consume bytes to use as the input string.
  std::string input_string = stream.ConsumeBytesAsString(1024);

  // Create an encoding structure.
  struct encoding enc;
  memset(&enc, 0, sizeof(enc));
  enc.name = encoding_name.c_str();

  // Create a pointer to the input string.
  char *input_ptr = input_string.data();

  // Create a pointer to the end of the input string.
  char *input_end = input_ptr + input_string.size();

  // Create a pointer to the next token.
  char *next_tok_ptr;

  // Call the function to be fuzzed.
  int result = initScanContentNS(&enc, input_ptr, input_end, &next_tok_ptr);

  // Consume the remaining bytes.
  stream.ConsumeRemainingBytes();

  return result;
}