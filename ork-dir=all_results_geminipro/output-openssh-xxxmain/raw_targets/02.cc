#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t argc = stream.ConsumeIntegral<size_t>();
  std::vector<std::string> args;
  for (size_t i = 0; i < argc; i++) {
    args.push_back(stream.ConsumeRemainingBytesAsString());
  }

  char** argv = new char*[argc + 1];
  for (size_t i = 0; i < argc; i++) {
    argv[i] = new char[args[i].size() + 1];
    strcpy(argv[i], args[i].c_str());
  }
  argv[argc] = nullptr;

  int ret = xxxmain(argc, argv);

  for (size_t i = 0; i < argc; i++) {
    delete[] argv[i];
  }
  delete[] argv;

  return ret;
}