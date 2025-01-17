#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "openjpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the JPEG 2000 codec.
  opj_codec_t* codec = opj_create_decompress(OPJ_CODEC_J2K);
  if (codec == nullptr) {
    return 0;
  }

  // Create a stream.
  opj_stream_private_t* stream = opj_stream_create_default_file_stream("dummy.jp2", 1);
  if (stream == nullptr) {
    opj_destroy_codec(codec);
    return 0;
  }

  // Create an image.
  opj_image_t* image = opj_image_create(0, nullptr, OPJ_CLRSPC_UNKNOWN);
  if (image == nullptr) {
    opj_stream_destroy(stream);
    opj_destroy_codec(codec);
    return 0;
  }

  // Create an event manager.
  opj_event_mgr_t event_mgr;
  event_mgr.error_handler = nullptr;
  event_mgr.warning_handler = nullptr;
  event_mgr.info_handler = nullptr;

  // Get the tile index from the fuzzer data.
  int tile_index = stream.ConsumeIntegral<int>();

  // Call the function to fuzz.
  int result = opj_j2k_get_tile((opj_j2k_t*)codec, stream, image, &event_mgr, tile_index);

  // Clean up.
  opj_image_destroy(image);
  opj_stream_destroy(stream);
  opj_destroy_codec(codec);

  return 0;
}