#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int argc = stream.ConsumeIntegralInRange<int>(1, 5);  // Limiting to 5 arguments
  std::vector<std::string> argv_strings;
  std::vector<char*> argv;

  for (int i = 0; i < argc; ++i) {
    argv_strings.push_back(stream.ConsumeRandomLengthString());
  }

  for (auto& str : argv_strings) {
    argv.push_back(const_cast<char*>(str.c_str()));
  }

  // Add a null pointer at the end of argv as per convention
  argv.push_back(nullptr);

  main2(argc, argv.data());

  return 0;
}