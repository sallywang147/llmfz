#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // We need to ensure that name_len is less than or equal to the remaining size of the data
  size_t name_len = stream.remaining_bytes() / sizeof(size_t);
  std::vector<size_t> name = stream.ConsumeIntegralVector<size_t>(name_len);
  int val = stream.ConsumeIntegral<int>();

  register_int_index(name.data(), name_len, val);

  return 0;
}