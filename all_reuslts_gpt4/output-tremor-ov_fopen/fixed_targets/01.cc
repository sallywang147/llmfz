#include <fuzzer/FuzzedDataProvider.h>
#include <vorbis/vorbisfile.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the data to it.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }
  FILE *file = fdopen(fd, "wb");
  if (!file) {
    close(fd);
    return 0;
  }
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), file);
  fclose(file);

  // Now that we have a file, we can call ov_fopen.
  OggVorbis_File vf;
  int result = ov_fopen(filename, &vf);
  if (result == 0) {
    ov_clear(&vf);
  }

  // Clean up the temporary file.
  remove(filename);

  return 0;
}