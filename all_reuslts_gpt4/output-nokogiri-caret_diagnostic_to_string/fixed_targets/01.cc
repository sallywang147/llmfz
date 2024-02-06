#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create and initialize GumboInternalError
  GumboInternalError error;
  error.type = static_cast<GumboErrorType>(stream.ConsumeIntegralInRange<int>(1, 9));
  error.position.offset = stream.ConsumeIntegral<size_t>();
  error.position.line = stream.ConsumeIntegral<size_t>();
  error.position.column = stream.ConsumeIntegral<size_t>();
  error.original_text = stream.ConsumeRandomLengthString().c_str();

  // Create and initialize source_text
  std::string source_text_str = stream.ConsumeRemainingBytesAsString();
  char* source_text = const_cast<char*>(source_text_str.c_str());
  size_t source_length = source_text_str.length();

  // Create and initialize GumboStringBuffer
  GumboStringBuffer output;
  gumbo_string_buffer_init(&output);

  // Call function under test
  caret_diagnostic_to_string(&error, source_text, source_length, &output);

  // Clean up
  gumbo_string_buffer_destroy(&output);

  return 0;
}