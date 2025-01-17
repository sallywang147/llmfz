 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv;
  for (int i = 0; i < argc; ++i) {
    argv.push_back(stream.ConsumeRemainingBytesAsString());
  }
  void** argv_ptrs = static_cast<void**>(calloc(argc, sizeof(void*)));
  for (int i = 0; i < argc; ++i) {
    argv_ptrs[i] = const_cast<char*>(argv[i].c_str());
  }
  init(argc, argv_ptrs);
  free(argv_ptrs);
  return 0;
}