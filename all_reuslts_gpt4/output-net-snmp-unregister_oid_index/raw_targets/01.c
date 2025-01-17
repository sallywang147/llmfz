#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern int unregister_oid_index(size_t * name, size_t name_len, size_t * value, size_t value_len);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t half_size = size / 2;
  
  std::vector<size_t> name = stream.ConsumeIntegralVector<size_t>(half_size);
  std::vector<size_t> value = stream.ConsumeIntegralVector<size_t>(half_size);

  unregister_oid_index(name.data(), name.size(), value.data(), value.size());

  return 0;
}