#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize required parameters for the function
  GumboInternalError error;
  error.type = static_cast<GumboErrorType>(stream.ConsumeIntegralInRange<int>(1, 9));
  error.position = stream.ConsumeIntegral<size_t>();
  error.original_text = stream.ConsumeRandomLengthString().c_str();

  size_t source_length = stream.remaining_bytes() / 2;
  char* source_text = stream.ConsumeBytesAsString(source_length).c_str();

  char* output = nullptr;

  // Call the function to fuzz
  gumbo_caret_diagnostic_to_string(&error, source_text, source_length, &output);

  // Free the output string if it was allocated
  if (output != nullptr) {
    free(output);
  }

  return 0;
}