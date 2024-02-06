#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "cd.h"

struct Cd {
  int id;
  char title[30];
  char artist[30];
  int tracks;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Cd cd;
  cd.id = stream.ConsumeIntegral<int>();
  std::string title = stream.ConsumeBytesAsString(29);
  strncpy(cd.title, title.c_str(), sizeof(cd.title) - 1);
  cd.title[sizeof(cd.title) - 1] = '\0';
  std::string artist = stream.ConsumeBytesAsString(29);
  strncpy(cd.artist, artist.c_str(), sizeof(cd.artist) - 1);
  cd.artist[sizeof(cd.artist) - 1] = '\0';
  cd.tracks = stream.ConsumeIntegral<int>();

  cd_dump(&cd);

  return 0;
}