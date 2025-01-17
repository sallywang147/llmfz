#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" char * register_string_index(size_t * name, size_t name_len, char * cp);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t name_len = stream.ConsumeIntegral<size_t>();
  // Ensure name_len is not larger than the remaining data.
  if (name_len > stream.remaining_bytes()) {
    name_len = stream.remaining_bytes();
  }

  std::vector<size_t> name = stream.ConsumeBytes<size_t>(name_len);
  std::string cp = stream.ConsumeRemainingBytesAsString();

  char *result = register_string_index(name.data(), name.size(), const_cast<char*>(cp.c_str()));

  return 0;
}