#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t name_len = stream.ConsumeIntegral<size_t>();
  std::vector<size_t> name = stream.ConsumeIntegralVector<size_t>(name_len);

  const size_t value_len = stream.ConsumeIntegral<size_t>();
  std::vector<size_t> value = stream.ConsumeIntegralVector<size_t>(value_len);

  unregister_oid_index(name.data(), name_len, value.data(), value_len);

  return 0;
}