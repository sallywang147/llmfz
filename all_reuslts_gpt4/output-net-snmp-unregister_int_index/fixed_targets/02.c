#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern int unregister_int_index(size_t * name, size_t name_len, int val);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t name_len = stream.remaining_bytes() / sizeof(size_t);
  std::vector<size_t> name = stream.ConsumeIntegralVector<size_t>(name_len);
  const int val = stream.ConsumeIntegral<int>();

  unregister_int_index(name.data(), name.size(), val);

  return 0;
}