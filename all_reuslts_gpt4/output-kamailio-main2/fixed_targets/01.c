#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int main2(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume up to 10 arguments for argv.
  int argc = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<std::string> argv_strings;
  std::vector<char*> argv;

  // Consume strings for each argument.
  for (int i = 0; i < argc; ++i) {
    argv_strings.push_back(stream.ConsumeRandomLengthString());
  }

  // Convert strings to char* for argv.
  for (auto& str : argv_strings) {
    argv.push_back(const_cast<char*>(str.c_str()));
  }

  // Ensure argv is null-terminated.
  argv.push_back(nullptr);

  main2(argc, argv.data());

  return 0;
}