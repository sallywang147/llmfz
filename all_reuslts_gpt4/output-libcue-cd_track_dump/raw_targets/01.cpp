#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cd_track.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Track track;
  track.number = stream.ConsumeIntegral<int>();
  track.start = stream.ConsumeIntegral<int>();
  track.length = stream.ConsumeIntegral<int>();
  track.type = stream.ConsumeEnum<TrackType>();
  
  cd_track_dump(&track);
  
  return 0;
}