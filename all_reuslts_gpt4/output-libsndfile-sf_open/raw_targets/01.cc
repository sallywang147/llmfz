#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  SF_INFO sfinfo;
  sfinfo.samplerate = stream.ConsumeIntegral<int>();
  sfinfo.frames = stream.ConsumeIntegral<sf_count_t>();
  sfinfo.channels = stream.ConsumeIntegral<int>();
  sfinfo.format = stream.ConsumeIntegral<int>();
  sfinfo.sections = stream.ConsumeIntegral<int>();
  sfinfo.seekable = stream.ConsumeIntegral<int>();

  std::string path = stream.ConsumeRemainingBytesAsString();
  int mode = stream.ConsumeIntegral<int>();

  struct sf_private_tag *sf = sf_open(path.c_str(), mode, &sfinfo);

  if (sf != nullptr) {
    sf_close(sf);
  }

  return 0;
}