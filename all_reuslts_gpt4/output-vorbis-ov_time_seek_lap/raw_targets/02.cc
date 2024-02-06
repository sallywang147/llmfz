#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vorbis/vorbisfile.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize OggVorbis_File
  OggVorbis_File vf;
  ov_clear(&vf);

  // Create a buffer for the input data
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  
  // Initialize the OggVorbis_File with the data
  if (ov_open_callbacks(buffer.data(), &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
    return 0;
  }
  
  // Generate a random position for the seek
  double pos = stream.ConsumeFloatingPoint<double>();

  // Call the target function
  ov_time_seek_lap(&vf, pos);

  // Clean up
  ov_clear(&vf);

  return 0;
}