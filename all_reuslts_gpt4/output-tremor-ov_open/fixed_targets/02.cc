#include <fuzzer/FuzzedDataProvider.h>
#include <vorbis/vorbisfile.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the OggVorbis_File struct.
  OggVorbis_File vf;
  memset(&vf, 0, sizeof(vf));

  // Create a FuzzedDataProvider instance.
  FuzzedDataProvider provider(data, size);

  // Consume data from the provider to create a buffer.
  const size_t buffer_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  auto buffer = provider.ConsumeBytes<char>(buffer_size);

  // Create a temp file and write the buffer data to it.
  FILE* file = tmpfile();
  if (file == nullptr) {
    return 0;
  }
  fwrite(buffer.data(), 1, buffer.size(), file);
  rewind(file);

  // Call the target function.
  int ret = ov_open(file, &vf, nullptr, 0);

  // Clean up.
  if (ret == 0) {
    ov_clear(&vf);
  }
  fclose(file);

  return 0;
}