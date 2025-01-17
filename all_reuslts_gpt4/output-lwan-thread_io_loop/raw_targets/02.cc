#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" char* thread_io_loop(char* data);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string fuzzed_data = stream.ConsumeRemainingBytesAsString();
  
  // Call the function under test.
  char* result = thread_io_loop(const_cast<char*>(fuzzed_data.c_str()));

  // Free the memory if necessary.
  if (result != nullptr) {
    free(result);
  }

  return 0;
}