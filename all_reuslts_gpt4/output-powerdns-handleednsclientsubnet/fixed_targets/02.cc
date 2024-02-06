#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

extern bool handleEDNSClientSubnet(std::vector<uint8_t>*, size_t, size_t, char*, char*, bool, std::string*);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> vec = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2);
  size_t size1 = stream.ConsumeIntegral<size_t>();
  size_t size2 = stream.ConsumeIntegral<size_t>();
  std::string str1 = stream.ConsumeRandomLengthString();
  char* char1 = const_cast<char*>(str1.c_str());
  std::string str2 = stream.ConsumeRandomLengthString();
  char* char2 = const_cast<char*>(str2.c_str());
  bool bool1 = stream.ConsumeBool();
  std::string str3 = stream.ConsumeRemainingBytesAsString();
  std::string* str_ptr = &str3;

  handleEDNSClientSubnet(&vec, size1, size2, char1, char2, bool1, str_ptr);

  return 0;
}