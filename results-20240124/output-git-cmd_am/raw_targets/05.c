 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<char*> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str());
  }
  const char* envp = stream.ConsumeRemainingBytesAsString().c_str();

  cmd_am(argc, argv.data(), const_cast<char*>(envp));
  return 0;
}