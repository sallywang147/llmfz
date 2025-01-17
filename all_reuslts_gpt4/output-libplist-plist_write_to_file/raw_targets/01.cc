#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string plist = stream.ConsumeRandomLengthString();
  std::string filename = "/dev/null"; // We write to /dev/null to avoid disk I/O in fuzzing
  int format = stream.ConsumeIntegral<int>();
  int options = stream.ConsumeIntegral<int>();

  plist_write_to_file(const_cast<char*>(plist.c_str()), const_cast<char*>(filename.c_str()), format, options);

  return 0;
}