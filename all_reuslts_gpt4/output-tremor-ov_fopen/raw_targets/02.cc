#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vorbis/vorbisfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data to it.
  FILE* tmp = tmpfile();
  if (!tmp) {
    return 0;
  }
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), tmp);
  fflush(tmp);
  rewind(tmp);

  // Get the name of the temporary file.
  int fd = fileno(tmp);
  char path[1024];
  snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);

  // Call the target function.
  OggVorbis_File vf;
  int res = ov_fopen(path, &vf);

  // Do cleanup.
  if (res == 0) {
    ov_clear(&vf);
  }
  fclose(tmp);

  return 0;
}