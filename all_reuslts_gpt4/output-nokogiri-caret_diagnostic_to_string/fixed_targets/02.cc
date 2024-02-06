#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  GumboStringBuffer output;
  gumbo_string_buffer_init(&output);

  GumboInternalError error;
  error.type = static_cast<GumboErrorType>(provider.ConsumeIntegralInRange<int>(0, 9));
  error.position.offset = provider.ConsumeIntegral<size_t>();
  error.position.line = provider.ConsumeIntegral<size_t>();
  error.position.column = provider.ConsumeIntegral<size_t>();
  error.original_text = reinterpret_cast<const char*>(provider.ConsumeRemainingBytes().data());

  std::string source_text = provider.ConsumeRandomLengthString();
  size_t source_length = provider.ConsumeIntegralInRange<size_t>(0, source_text.size());

  caret_diagnostic_to_string(&error, const_cast<char*>(source_text.data()), source_length, &output);

  gumbo_string_buffer_destroy(&output);

  return 0;
}