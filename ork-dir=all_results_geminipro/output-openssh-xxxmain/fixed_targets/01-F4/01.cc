#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_args = stream.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<std::string> args;
  for (size_t i = 0; i < num_args; ++i) {
    args.push_back(stream.ConsumeRemainingBytesAsString());
  }
  char** argv = new char*[args.size() + 1];
  for (size_t i = 0; i < args.size(); ++i) {
    argv[i] = new char[args[i].size() + 1];
    strcpy(argv[i], args[i].c_str());
  }
  argv[args.size()] = nullptr;
  int ret = main(static_cast<int>(args.size()), argv);  // Fix: use main instead of xxxmain
  for (size_t i = 0; i < args.size(); ++i) {
    delete[] argv[i];
  }
  delete[] argv;
  return ret;
}

int main(int argc, char** argv) {
  // Your code here
  return 0;
}