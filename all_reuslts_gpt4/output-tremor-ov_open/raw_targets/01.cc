#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/vorbisfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume some bytes for the initial buffer
  size_t initial_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string initial = stream.ConsumeBytesAsString(initial_size);
  size -= initial_size;

  // Prepare a memory file
  FILE *f = fmemopen((void*)stream.data(), size, "rb");
  if (!f) {
    return 0;
  }

  // Initialize a vorbis file
  OggVorbis_File vf;
  int ret = ov_open(f, &vf, initial.empty() ? NULL : &initial[0], initial.size());

  // Cleanup
  if (ret == 0) {
    ov_clear(&vf);
  }
  fclose(f);

  return 0;
}