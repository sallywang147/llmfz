#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int omain(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data to create argc and argv
  const int argc = stream.ConsumeIntegralInRange<int>(1, 10);
  std::vector<std::string> arg_strings;
  for (int i = 0; i < argc; ++i) {
    arg_strings.push_back(stream.ConsumeRandomLengthString());
  }

  // Prepare argv
  std::vector<char*> argv;
  for (std::string& arg : arg_strings) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  argv.push_back(nullptr);  // argv must be null-terminated

  // Call the target function
  omain(argc, argv.data());

  return 0;
}