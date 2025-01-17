#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "speex/speex.h"
#include "speex/speex_bits.h"

extern "C" {
#include "speex/speex_preprocess.h"
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  SpeexBits bits;
  speex_bits_init(&bits);
  speex_bits_read_from(&bits, data, size);

  int nsf = 10;
  int p = 1;
  int complexity = 1;
  int update_target = 1;
  float exc[10] = {0};
  float r[10] = {0};
  float target[10] = {0};
  float ak[10] = {0};
  float awk1[10] = {0};
  float awk2[10] = {0};
  char par[10] = {0};
  char stack[1000] = {0};

  split_cb_search_shape_sign(target, ak, awk1, awk2, par, p, nsf, exc, r, &bits, stack, complexity, update_target);

  speex_bits_destroy(&bits);
}