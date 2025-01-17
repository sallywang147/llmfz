#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume half of the data for plist_data
  size_t half_size = size / 2;
  std::string plist_data = stream.ConsumeBytesAsString(half_size);
  
  // Consume the rest of the data for plist
  std::string plist = stream.ConsumeRemainingBytesAsString();
  
  int format = 0;
  plist_from_memory(const_cast<char *>(plist_data.c_str()), plist_data.size(), const_cast<char **>(&plist), &format);
  
  return 0;
}