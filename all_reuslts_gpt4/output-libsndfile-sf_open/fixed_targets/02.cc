#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int mode = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string path = stream.ConsumeRandomLengthString();
  char *path_ptr = const_cast<char*>(path.c_str());

  // Extract to user defined object
  SF_INFO sfinfo;
  sfinfo.frames = stream.ConsumeIntegral<sf_count_t>();
  sfinfo.samplerate = stream.ConsumeIntegral<int>();
  sfinfo.channels = stream.ConsumeIntegral<int>();
  sfinfo.format = stream.ConsumeIntegral<int>();
  sfinfo.sections = stream.ConsumeIntegral<int>();
  sfinfo.seekable = stream.ConsumeIntegral<int>();

  struct sf_private_tag *sf = sf_open(path_ptr, mode, &sfinfo);
  if (sf != nullptr) {
    sf_close(sf);
  }

  return 0;
}