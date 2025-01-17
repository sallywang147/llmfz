#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t name_len = stream.ConsumeIntegral<size_t>();
  const std::vector<uint8_t> name_bytes =
      stream.ConsumeBytes<uint8_t>(name_len);
  const size_t* name = reinterpret_cast<const size_t*>(name_bytes.data());
  const int val = stream.ConsumeIntegral<int>();

  register_int_index(const_cast<size_t*>(name), name_len, val);
  return 0;
}