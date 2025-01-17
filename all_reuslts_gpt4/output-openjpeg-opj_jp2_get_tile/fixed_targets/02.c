#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <vector>

#include "openjpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  opj_jp2_t *jp2 = opj_jp2_create(true);
  if (!jp2) {
    return 0;
  }

  opj_stream_private_t *l_stream = opj_stream_create_default_file_stream("test.j2k", 1);
  if (!l_stream) {
    opj_jp2_destroy(jp2);
    return 0;
  }

  opj_image_t *image = opj_image_create(0, NULL, OPJ_CLRSPC_SRGB);
  if (!image) {
    opj_stream_destroy(l_stream);
    opj_jp2_destroy(jp2);
    return 0;
  }

  opj_event_mgr_t event_mgr;
  event_mgr.error_handler = NULL;
  event_mgr.warning_handler = NULL;
  event_mgr.info_handler = NULL;

  int tile_index = stream.ConsumeIntegral<int>();

  opj_jp2_get_tile(jp2, l_stream, image, &event_mgr, tile_index);

  opj_image_destroy(image);
  opj_stream_destroy(l_stream);
  opj_jp2_destroy(jp2);

  return 0;
}