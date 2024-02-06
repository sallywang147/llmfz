#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include <pcre2.h>
#include <pcre2posix.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t memory_size = stream.ConsumeIntegralInRange<size_t>(0, 1024 * 1024);
  std::vector<char> memory_data(memory_size);
  stream.ConsumeBytes<char>(memory_data.data(), memory_size);

  struct pcre2_real_general_context_8* context =
      pcre2_general_context_create_8(malloc, free, memory_data.data());
  if (context == nullptr) {
    return 0;
  }

  pcre2_general_context_free(context);
  return 0;
}