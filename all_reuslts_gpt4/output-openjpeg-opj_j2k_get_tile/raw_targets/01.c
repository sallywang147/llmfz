#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "openjpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  opj_j2k_t *j2k = opj_j2k_create_compress(CODEC_J2K);
  if (!j2k) {
    return 0;
  }

  opj_stream_private_t *stream_private = opj_stream_create_default_buffer_stream((void *)data, 1);
  if (!stream_private) {
    opj_j2k_destroy(j2k);
    return 0;
  }

  opj_image_t *image = opj_image_create(0, NULL, CLRSPC_UNKNOWN);
  if (!image) {
    opj_stream_destroy(stream_private);
    opj_j2k_destroy(j2k);
    return 0;
  }

  opj_event_mgr_t event_mgr;
  memset(&event_mgr, 0, sizeof(event_mgr));

  int tile_index = stream.ConsumeIntegral<int>();

  opj_j2k_get_tile(j2k, stream_private, image, &event_mgr, tile_index);

  opj_image_destroy(image);
  opj_stream_destroy(stream_private);
  opj_j2k_destroy(j2k);

  return 0;
}