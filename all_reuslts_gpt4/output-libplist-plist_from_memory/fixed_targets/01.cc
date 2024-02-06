#include <fuzzer/FuzzedDataProvider.h>
#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string plist_data = stream.ConsumeRemainingBytesAsString();
  char* plist = nullptr;
  int format = 0;

  plist_from_memory(const_cast<char*>(plist_data.c_str()), plist_data.size(), &plist, &format);

  if (plist != nullptr) {
    free(plist);
  }

  return 0;
}