 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegralInRange<int>(1, 100);
  std::vector<std::string> argv_vector;
  for (int i = 0; i < argc; i++) {
    argv_vector.push_back(stream.ConsumeRandomLengthString());
  }
  std::vector<char*> argv_ptrs;
  for (const auto& arg : argv_vector) {
    char* arg_ptr = const_cast<char*>(arg.c_str());
    argv_ptrs.push_back(arg_ptr);
  }
  argv_ptrs.push_back(nullptr);
  main2(argc, argv_ptrs.data());
  return 0;
}