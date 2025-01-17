#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cd_track.h"

struct Track {
  int id;
  char name[50];
  int duration;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Track track;
  track.id = stream.ConsumeIntegral<int>();
  std::string name = stream.ConsumeBytesAsString(49);
  strncpy(track.name, name.c_str(), sizeof(track.name) - 1);
  track.name[sizeof(track.name) - 1] = '\0';  // Ensure null-termination
  track.duration = stream.ConsumeIntegral<int>();

  cd_track_dump(&track);

  return 0;
}