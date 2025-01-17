#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern bool handleEDNSClientSubnet(std::vector<uint8_t>*, size_t, size_t, char*, char*, bool, std::string*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> vector_arg;
  size_t size_arg1 = stream.ConsumeIntegral<size_t>();
  size_t size_arg2 = stream.ConsumeIntegral<size_t>();
  std::string str_arg = stream.ConsumeRandomLengthString();
  std::string str_arg2 = stream.ConsumeRandomLengthString();
  bool bool_arg = stream.ConsumeBool();
  std::string str_arg3;

  char *char_arg1 = const_cast<char*>(str_arg.c_str());
  char *char_arg2 = const_cast<char*>(str_arg2.c_str());

  handleEDNSClientSubnet(&vector_arg, size_arg1, size_arg2, char_arg1, char_arg2, bool_arg, &str_arg3);

  return 0;
}