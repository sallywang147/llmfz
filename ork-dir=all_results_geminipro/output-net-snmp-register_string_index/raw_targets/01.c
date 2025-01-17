#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t name_len = stream.ConsumeIntegral<size_t>();
  const std::string name = stream.ConsumeRandomLengthString(name_len);
  const std::string cp = stream.ConsumeRemainingBytesAsString();

  char *result =
      register_string_index(reinterpret_cast<size_t*>(const_cast<char*>(name.c_str())),
                            name_len, const_cast<char*>(cp.c_str()));
  free(result);
  return 0;
}