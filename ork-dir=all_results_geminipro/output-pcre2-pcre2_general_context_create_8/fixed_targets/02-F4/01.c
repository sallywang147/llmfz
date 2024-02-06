#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "pcre2.h"

extern "C" {
#include "pcre2_config.h"
#include "pcre2_general.h"
#include "pcre2_jit_compile.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t memory_size = stream.ConsumeIntegralInRange<size_t>(0, 1<<20);
  std::vector<char> memory_data(memory_size);
  stream.ConsumeBytes<char>(memory_data.data(), memory_size);
  struct pcre2_real_general_context_8 *ctx =
      pcre2_general_context_create_8(nullptr, nullptr, memory_data.data(), memory_size);
  if (ctx == nullptr) {
    return 0;
  }
  pcre2_general_context_free_8(ctx);
  return 0;
}