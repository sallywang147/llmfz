#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OggVorbis_File struct
  OggVorbis_File vf;
  memset(&vf, 0, sizeof(vf));

  // Initialize a virtual file system callbacks structure
  ov_callbacks callbacks = {
    (size_t (*)(void *, size_t, size_t, void *)) 0,
    (int (*)(void *, ogg_int64_t, int)) 0,
    (int (*)(void *)) 0,
    (long (*)(void *, ogg_int64_t, int)) 0,
  };

  // Open the vorbis file. This is safe even if the input data is not a valid vorbis file.
  if (ov_open_callbacks(data, &vf, NULL, 0, callbacks) < 0) {
    return 0;
  }

  // Get flag from the fuzzer input
  int flag = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  ov_halfrate(&vf, flag);

  // Close the vorbis file
  ov_clear(&vf);

  return 0;
}