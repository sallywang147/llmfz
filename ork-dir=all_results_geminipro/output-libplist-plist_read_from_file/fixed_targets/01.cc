#include <plist/plist.h>
#include <stdio.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRemainingBytesAsString();

  char *plist;
  int format;
  int ret = plist_read_file(filename.c_str(), &plist, &format);
  if (ret == 0) {
    plist_free(plist);
  }

  return 0;
}