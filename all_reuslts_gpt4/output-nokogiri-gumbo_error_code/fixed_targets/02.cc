#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct GumboInternalError error;

  error.type = stream.ConsumeEnum<GumboErrorType>();
  error.position = stream.ConsumeIntegral<GumboSourcePosition>();
  error.original_text = stream.ConsumeRandomLengthString().c_str();

  char* result = gumbo_error_code(&error);
  
  return 0;
}