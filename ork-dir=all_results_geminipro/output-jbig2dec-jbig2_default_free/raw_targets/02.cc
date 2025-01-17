#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t requested_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* p = static_cast<char*>(std::malloc(requested_size));
  stream.ConsumeBytes(p, requested_size);
  jbig2_default_free(nullptr, p);
  return 0;
}