#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" size_t ZydisStdinRead(char * ctx, char * buf, size_t max_len);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for 'ctx'
  std::string ctx = stream.ConsumeRandomLengthString();
  
  // Consume data for 'buf'
  std::string buf = stream.ConsumeRandomLengthString();

  // Consume data for 'max_len'
  size_t max_len = stream.ConsumeIntegral<size_t>();

  // Ensure 'max_len' is not greater than 'buf' size
  if (max_len > buf.size()) {
    max_len = buf.size();
  }

  // Call the function under test
  ZydisStdinRead(const_cast<char*>(ctx.c_str()), const_cast<char*>(buf.c_str()), max_len);

  return 0;
}