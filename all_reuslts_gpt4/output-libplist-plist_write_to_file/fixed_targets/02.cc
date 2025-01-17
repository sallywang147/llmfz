#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data to create a plist string
  size_t plist_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string plist = stream.ConsumeBytesAsString(plist_size);

  // Consume data to create a filename
  std::string filename = stream.ConsumeRemainingBytesAsString();

  // Define format and options
  int format = stream.ConsumeIntegral<int>();
  int options = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  plist_write_to_file(const_cast<char*>(plist.c_str()), const_cast<char*>(filename.c_str()), format, options);

  return 0;
}