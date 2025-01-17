#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ogg/ogg.h>
#include <opus/opus.h>
#include <opus/opusfile.h>

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

static OggOpusFile *of;
static OpusDecoder *decoder;
static int channels;
static int rate;

static void init_decoder(const uint8_t *data, size_t size) {
  of = op_open_memory(data, size, NULL);
  if (of == NULL) {
    exit(1);
  }
  decoder = op_decoder_create(rate, channels, NULL);
  if (decoder == NULL) {
    exit(1);
  }
}

static void destroy_decoder() {
  op_decoder_destroy(decoder);
  op_close(of);
}

static int decode_frame(const uint8_t *data, size_t size, float *pcm, int buf_size) {
  int li = 0;
  int ret = op_read_float(of, pcm, buf_size, &li);
  if (ret < 0) {
    return ret;
  }
  return li;
}

DEFINE_PROTO_FUZZER(LLVMFuzzerTestOneInput, uint8_t *data, size_t size) {
  init_decoder(data, size);
  float pcm[4096];
  while (decode_frame(data, size, pcm, sizeof(pcm) / sizeof(pcm[0])) > 0) {
  }
  destroy_decoder();
}