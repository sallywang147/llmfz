#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern int wgnutls_write(int fd, char * buf, int bufsize, char * arg);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Consume data for 'buf' and 'arg' parameters
  const size_t buf_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes() / 2);
  std::string buf = provider.ConsumeBytesAsString(buf_size);
  std::string arg = provider.ConsumeRemainingBytesAsString();

  // Call the function with fuzzed data
  wgnutls_write(-1, buf.data(), buf.size(), arg.data());

  return 0;
}