#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <mntent.h>
#include <mnttab.h>

extern "C" {
#include <mntent.h>
#include <mnttab.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  struct mnttab mnttab;
  FILE* fp = fopen(filename.c_str(), "r");
  if (fp == NULL) {
    return -1;
  }
  int ret = getmntent_r(fp, &mnttab, &mnttab);
  fclose(fp);
  return ret;
}