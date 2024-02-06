#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t ZydisStdinRead(char * ctx, char * buf, size_t max_len);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume a string for the `ctx` parameter
  std::string ctx = stream.ConsumeRandomLengthString();
  
  // Consume a size for the `max_len` parameter
  size_t max_len = stream.ConsumeIntegral<size_t>();

  // Create a buffer for the `buf` parameter
  std::vector<char> buf(max_len);

  // Call the function to fuzz
  ZydisStdinRead(ctx.data(), buf.data(), max_len);

  return 0;
}