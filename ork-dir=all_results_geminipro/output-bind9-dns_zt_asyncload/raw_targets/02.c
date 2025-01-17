#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "dns.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int zt_size = stream.ConsumeIntegral<int>();
  struct dns_zt* zt =
      static_cast<struct dns_zt*>(std::malloc(sizeof(struct dns_zt) * zt_size));
  if (zt == nullptr) {
    return 0;
  }
  const bool newonly = stream.ConsumeBool();
  const size_t arg_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* arg = static_cast<char*>(std::malloc(arg_size));
  if (arg == nullptr) {
    std::free(zt);
    return 0;
  }
  stream.ConsumeBytes<char>(arg, arg_size);
  dns_zt_asyncload(zt, newonly, nullptr, arg);
  std::free(zt);
  std::free(arg);
  return 0;
}