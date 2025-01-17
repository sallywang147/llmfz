#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the GumboInternalError struct
  GumboInternalError error;
  error.type = static_cast<GumboErrorType>(stream.ConsumeIntegralInRange<int>(0, 7));
  error.position = static_cast<GumboSourcePosition>(stream.ConsumeIntegral<GumboSourcePosition>());
  error.original_text = stream.ConsumeRandomLengthString().c_str();
  error.v = static_cast<GumboVector>(stream.ConsumeIntegral<GumboVector>());

  // Define and initialize the source_text
  std::string source_text = stream.ConsumeRandomLengthString();
  char* source_text_ptr = const_cast<char*>(source_text.c_str());

  // Define and initialize the source_length
  size_t source_length = source_text.length();

  // Call the target function
  gumbo_print_caret_diagnostic(&error, source_text_ptr, source_length);

  return 0;
}