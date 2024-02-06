#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "openjpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenJPEG structures
  opj_j2k_t* j2k = opj_j2k_create_decompress(CODEC_J2K);
  if (!j2k) {
    return 0;
  }

  opj_stream_private_t* stream_private = opj_stream_create_default_buffer_stream((void*)data, 0);
  if (!stream_private) {
    opj_j2k_destroy(j2k);
    return 0;
  }

  opj_event_mgr_t event_mgr;
  event_mgr.error_handler = nullptr;
  event_mgr.warning_handler = nullptr;
  event_mgr.info_handler = nullptr;

  // Call the function to fuzz
  int result = opj_j2k_decode_one_tile(j2k, stream_private, &event_mgr);

  // Cleanup
  opj_stream_destroy(stream_private);
  opj_j2k_destroy(j2k);

  return 0;
}