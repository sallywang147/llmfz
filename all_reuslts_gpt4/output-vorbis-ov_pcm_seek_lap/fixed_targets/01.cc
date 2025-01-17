#include <fuzzer/FuzzedDataProvider.h>
#include <vorbis/vorbisfile.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  OggVorbis_File vf;
  int open_result = ov_open_callbacks(&stream, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE);
  if (open_result < 0) {
    return 0;
  }

  size_t pos = stream.ConsumeIntegral<size_t>();
  ov_pcm_seek_lap(&vf, pos);

  ov_clear(&vf);
  return 0;
}

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  return 0;
}