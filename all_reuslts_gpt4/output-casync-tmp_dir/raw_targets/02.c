#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
  int tmp_dir(char ** ret);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume a string from the input data to use as the parameter.
  std::string str = stream.ConsumeRandomLengthString();
  char* ptr = const_cast<char*>(str.c_str());
  char** ret = &ptr;

  // Call the function under test.
  tmp_dir(ret);

  return 0;
}