#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
}

extern "C" char* register_string_index(size_t* name, size_t name_len,
                                       const char* cp);

extern "C" void free(void* ptr);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t name_len = stream.ConsumeIntegral<size_t>();
  const std::string name = stream.ConsumeRemainingBytesAsString();
  if (name.size() != name_len) {
    return 0;
  }
  const std::string cp = stream.ConsumeRemainingBytesAsString();
  char* result = register_string_index(
      reinterpret_cast<size_t*>(const_cast<char*>(name.c_str())), name_len,
      const_cast<char*>(cp.c_str()));
  free(result);
  return 0;
}
```

The issue was that the `register_string_index` function was not declared with `extern "C"`, which is necessary when calling a C function from C++ code. Adding `extern "C"` to the declaration of `register_string_index` fixes the issue.