#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" int main262(int argc, char **argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<std::string> arguments;
  while (stream.remaining_bytes() > 0) {
    std::string arg = stream.ConsumeRandomLengthString();
    if (!arg.empty()) {
      arguments.push_back(arg);
    }
  }

  if (arguments.empty()) {
    return 0;
  }

  std::vector<char*> argv;
  for (std::string& arg : arguments) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }

  argv.push_back(nullptr);  // argv must be null terminated

  main262(argv.size() - 1, argv.data());

  return 0;
}