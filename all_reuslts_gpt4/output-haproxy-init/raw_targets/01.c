#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Define the maximum number of arguments
  const int max_argc = 10;

  // Extract argc from the data stream
  int argc = stream.ConsumeIntegralInRange<int>(0, max_argc);

  // Create an array to hold the arguments
  char* argv[max_argc + 1]; // +1 for the null terminator

  // Fill the argv array with arguments from the data stream
  for (int i = 0; i < argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv[i] = const_cast<char*>(arg.c_str());
  }

  // Null-terminate the argv array
  argv[argc] = nullptr;

  // Call the target function
  init(argc, argv);

  return 0;
}