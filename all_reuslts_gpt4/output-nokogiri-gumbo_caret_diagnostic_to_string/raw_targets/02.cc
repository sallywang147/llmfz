#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize GumboInternalError struct
  GumboInternalError error;
  error.type = static_cast<GumboErrorType>(stream.ConsumeIntegralInRange<int>(1, 9));
  error.position = static_cast<GumboSourcePosition>(stream.ConsumeIntegralInRange<int>(0, 100));
  error.original_text = stream.ConsumeRandomLengthString().c_str();
  error.v = static_cast<GumboVector>(stream.ConsumeIntegralInRange<int>(0, 100));

  // Initialize source_text and source_length
  std::string source_text = stream.ConsumeRemainingBytesAsString();
  size_t source_length = source_text.size();

  // Initialize output
  char* output = nullptr;

  // Call the function
  size_t result = gumbo_caret_diagnostic_to_string(&error, const_cast<char*>(source_text.c_str()), source_length, &output);

  // Free the output string if it was allocated
  if (output) {
    free(output);
  }

  return 0;
}