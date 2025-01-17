#include <fuzzer/FuzzedDataProvider.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize vorbis file
  OggVorbis_File vf;
  memset(&vf, 0, sizeof(vf));

  // Create a callback structure
  ov_callbacks callbacks = {
      .read_func = [](void* ptr, size_t size, size_t nmemb, void* datasource) {
        FuzzedDataProvider* stream = static_cast<FuzzedDataProvider*>(datasource);
        const size_t requested_size = size * nmemb;
        const std::vector<uint8_t> data = stream->ConsumeBytes<uint8_t>(requested_size);
        memcpy(ptr, data.data(), data.size());
        return data.size();
      },
      .seek_func = [](void* datasource, ogg_int64_t offset, int whence) {
        return 0;
      },
      .close_func = [](void* datasource) {
        return 0;
      },
      .tell_func = [](void* datasource) {
        return 0;
      },
  };

  // Call ov_test_open
  if (ov_open_callbacks(&stream, &vf, NULL, 0, callbacks) == 0) {
    ov_test_open(&vf);
    ov_clear(&vf);
  }

  return 0;
}