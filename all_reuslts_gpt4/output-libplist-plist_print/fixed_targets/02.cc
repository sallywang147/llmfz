#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a null-terminated string from the input data
  std::string str(reinterpret_cast<const char*>(data), size);
  str.push_back('\0');

  // Call the target function
  plist_print(const_cast<char*>(str.c_str()));

  return 0;
}