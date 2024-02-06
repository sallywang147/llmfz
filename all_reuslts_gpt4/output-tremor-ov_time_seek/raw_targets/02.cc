#include <fuzzer/FuzzedDataProvider.h>
#include <vorbis/vorbisfile.h>

#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OggVorbis_File struct
  OggVorbis_File vf;
  vf.datasource = nullptr;
  vf.seek_func = nullptr;
  vf.tell_func = nullptr;
  vf.close_func = nullptr;
  vf.read_func = nullptr;
  vf.offset = 0;
  vf.end = 0;
  vf.oy = {};

  // Get the milliseconds from the stream
  size_t milliseconds = stream.ConsumeIntegral<size_t>();

  // Call the function to fuzz
  ov_time_seek(&vf, milliseconds);

  return 0;
}