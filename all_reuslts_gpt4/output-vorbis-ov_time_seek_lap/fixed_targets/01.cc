#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static const char* const filenames[] = {"", "corpus", "fuzzing"};
  static const int modes[] = {0, 1, 2, 3, 4};

  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  OggVorbis_File vf;
  int result = ov_open_callbacks(
      &vf, &vf, nullptr, 0,
      {[](void* ptr, size_t size, size_t nmemb, void* datasource) {
         return stream.ConsumeBytes<uint8_t>(size * nmemb).size() / size;
       },
       [](void* datasource, ogg_int64_t offset, int whence) {
         // We don't support seeking.
         return -1;
       },
       nullptr,
       [](void* datasource) {
         // We don't support closing.
         return EOF;
       }});
  
  if (result < 0) {
    return 0;
  }

  double pos = stream.ConsumeFloatingPoint<double>();
  ov_time_seek_lap(&vf, pos);

  ov_clear(&vf);

  return 0;
}