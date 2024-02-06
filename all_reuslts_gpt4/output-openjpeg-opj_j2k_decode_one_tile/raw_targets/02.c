#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "openjpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  opj_cparameters_t parameters;
  opj_set_default_decoder_parameters(&parameters);

  opj_codec_t* l_codec = opj_create_decompress(OPJ_CODEC_J2K);
  opj_set_info_handler(l_codec, info_callback,00);
  opj_set_warning_handler(l_codec, warning_callback,00);
  opj_set_error_handler(l_codec, error_callback,00);

  if (! opj_setup_decoder(l_codec, &parameters)) {
    opj_destroy_codec(l_codec);
    return 0;
  }

  opj_image_t* image = NULL;
  opj_stream_t *l_stream = opj_stream_create_default_buffer_stream((OPJ_BYTE *)data, 1);
  opj_read_header(l_stream, l_codec, &image);

  if (image) {
    opj_j2k_t* j2k = (opj_j2k_t*) l_codec->m_codec;
    opj_event_mgr_t event_mgr;
    opj_event_mgr_info_handler(&event_mgr, info_callback, NULL);
    opj_event_mgr_warning_handler(&event_mgr, warning_callback, NULL);
    opj_event_mgr_error_handler(&event_mgr, error_callback, NULL);
    opj_j2k_decode_one_tile(j2k, l_stream, &event_mgr);
  }

  opj_stream_destroy(l_stream);
  opj_destroy_codec(l_codec);
  opj_image_destroy(image);
  return 0;
}

static void info_callback(const char *msg, void *client_data) {
  (void)client_data;
  fprintf(stdout, "[INFO] %s", msg);
}

static void warning_callback(const char *msg, void *client_data) {
  (void)client_data;
  fprintf(stdout, "[WARNING] %s", msg);
}

static void error_callback(const char *msg, void *client_data) {
  (void)client_data;
  fprintf(stdout, "[ERROR] %s", msg);
}