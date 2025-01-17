#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  const char* data_ptr = reinterpret_cast<const char*>(bytes.data());
  const size_t data_size = bytes.size();

  struct DNSQuestion q;
  short option_code = stream.ConsumeIntegral<short>();
  std::string option_data = stream.ConsumeRemainingBytesAsString();

  bool ret = setEDNSOption(&q, option_code, &option_data);
  if (ret) {
    // Do something with the result.
  }

  return 0;
}