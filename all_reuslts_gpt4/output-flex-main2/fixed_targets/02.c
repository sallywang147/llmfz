#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data to create argc and argv.
  const uint8_t argc = stream.ConsumeIntegral<uint8_t>();
  std::vector<std::string> arg_strings;
  std::vector<char*> argv;

  for (size_t i = 0; i < argc; ++i) {
    if (stream.remaining_bytes() == 0) {
      break;
    }
    arg_strings.push_back(stream.ConsumeRandomLengthString());
    argv.push_back(const_cast<char*>(arg_strings.back().c_str()));
  }
  argv.push_back(nullptr);  // argv must be null terminated.

  // Call the target function.
  main2(argv.size() - 1, argv.data());

  return 0;
}