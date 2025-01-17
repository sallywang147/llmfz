#include <stdint.h>
#include <stdlib.h>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"
#include "fuzzer/FuzzedDataProvider.h"

// Opusfile fuzzing wrapper to help with automated fuzz testing. It's based on
// https://github.com/xiph/opusfile/blob/master/examples/opusfile_example.c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int ret;
  OggOpusFile *of = op_open_memory(data, size, &ret);
  if (!of)
    return 0;

  op_link_count(of);

  int link_index = -1;
  op_pcm_total(of, link_index);
  op_raw_total(of, link_index);
  op_pcm_tell(of);
  op_raw_tell(of);

  const int pcm_size = 120 * 48 * 2; // 120ms/ch@48kHz is recommended
  float pcm[pcm_size];
  int li = stream.ConsumeIntegral<int>();

  for (;;) {
    ret = op_read_float(of, pcm, pcm_size, &li);
    if (ret < 0) {
      break;
    }

    if (op_current_link(of) != link_index) {
      link_index = op_current_link(of);
      op_pcm_total(of, link_index);
      op_raw_total(of, link_index);
      op_pcm_tell(of);
      op_raw_tell(of);
      op_bitrate_instant(of);
    }

    if (ret == 0) {
      break;
    }
  }

  op_free(of);
  return 0;
}