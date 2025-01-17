#include "fuzzer/FuzzedDataProvider.h"

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "pcre2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pcre2_real_compile_context_8* context =
      pcre2_compile_context_create_8(nullptr);
  if (context == nullptr) {
    return 0;
  }

  const int newline = stream.ConsumeIntegral<int>();
  pcre2_set_newline_8(context, newline);
  pcre2_compile_context_free_8(context);
  return 0;
}