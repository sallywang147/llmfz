#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a GumboInternalError struct.
  GumboInternalError error;
  error.type = static_cast<GumboErrorType>(stream.ConsumeIntegralInRange<int>(1, 9));
  error.position.offset = stream.ConsumeIntegral<size_t>();
  error.position.line = stream.ConsumeIntegral<size_t>();
  error.position.column = stream.ConsumeIntegral<size_t>();
  error.original_text = stream.ConsumeRandomLengthString().c_str();
  error.v.text.start_pos.offset = stream.ConsumeIntegral<size_t>();
  error.v.text.start_pos.line = stream.ConsumeIntegral<size_t>();
  error.v.text.start_pos.column = stream.ConsumeIntegral<size_t>();
  error.v.text.end_pos.offset = stream.ConsumeIntegral<size_t>();
  error.v.text.end_pos.line = stream.ConsumeIntegral<size_t>();
  error.v.text.end_pos.column = stream.ConsumeIntegral<size_t>();

  // Create source_text from the remaining bytes.
  std::string source_text = stream.ConsumeRemainingBytesAsString();
  size_t source_length = source_text.size();

  // Call the function to fuzz.
  gumbo_print_caret_diagnostic(&error, const_cast<char*>(source_text.c_str()), source_length);

  return 0;
}