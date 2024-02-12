 #include <cups/cups.h>
#include <cups/ipp.h>
#include <cups/ppd.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(
      100, 10000);
  std::vector<uint8_t> buffer(buffer_size);
  for (auto& byte : buffer) {
    byte = stream.ConsumeIntegral<uint8_t>();
  }
  ipp_t *supported = ippNew();
  const char* result = _ppdCreateFromIPP(reinterpret_cast<char*>(buffer.data()),
                                        buffer_size, supported);
  ippDelete(supported);
  return 0;
}