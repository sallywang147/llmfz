#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int main2(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<std::string> arguments;
  while (stream.remaining_bytes() > 0) {
    arguments.push_back(stream.ConsumeRandomLengthString());
  }

  std::vector<char*> argv;
  for (auto& arg : arguments) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }

  argv.push_back(nullptr);  // argv must be null-terminated

  main2(argv.size(), argv.data());

  return 0;
}