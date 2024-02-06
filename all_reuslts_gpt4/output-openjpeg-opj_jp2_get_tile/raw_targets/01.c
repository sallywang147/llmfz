#include <fuzzer/FuzzedDataProvider.h>
#include "openjpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the JP2 decoder
  opj_jp2_t *jp2 = opj_jp2_create(true);
  if (jp2 == nullptr) {
    return 0;
  }

  // Create a stream
  opj_stream_private_t *stream = opj_stream_create_default_file_stream("test.jp2", 1);
  if (stream == nullptr) {
    opj_jp2_destroy(jp2);
    return 0;
  }

  // Create an image
  opj_image_t *image = opj_image_create(1, new opj_image_cmptparm_t, OPJ_CLRSPC_SRGB);
  if (image == nullptr) {
    opj_stream_destroy(stream);
    opj_jp2_destroy(jp2);
    return 0;
  }

  // Create an event manager
  opj_event_mgr_t event_mgr;
  event_mgr.error_handler = nullptr;
  event_mgr.warning_handler = nullptr;
  event_mgr.info_handler = nullptr;

  // Get a tile index
  int tile_index = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  opj_jp2_get_tile(jp2, stream, image, &event_mgr, tile_index);

  // Cleanup
  opj_image_destroy(image);
  opj_stream_destroy(stream);
  opj_jp2_destroy(jp2);

  return 0;
}