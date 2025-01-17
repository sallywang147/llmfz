#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opusfile/config.h"
#include "opusfile/include/opusfile.h"
#include <fuzzer/FuzzedDataProvider.h>

// Opusfile fuzzing wrapper to help with automated fuzz testing. It's based on
// https://github.com/xiph/opusfile/blob/master/examples/opusfile_example.c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int ret;
  OggOpusFile *of = op_open_memory(data, size, &ret);
  if (!of)
    return 0;

  FuzzedDataProvider stream(data, size);

  int link_index = -1;
  op_link_count(of);
  op_pcm_total(of, link_index);
  op_raw_total(of, link_index);
  op_pcm_tell(of);
  op_raw_tell(of);

  const int pcm_size = 120 * 48 * 2; // 120ms/ch@48kHz is recommended
  float pcm[pcm_size];
  for (;;) {
    ret = op_read_float_stereo(of, pcm, pcm_size);
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
      const OpusTags *tags = op_tags(of, link_index);
      for (int i = 0; i < tags->comments; ++i) {
        if (opus_tagncompare("METADATA_BLOCK_PICTURE", 22, tags->user_comments[i]) == 0) {
          OpusPictureTag pic;
          if (opus_picture_tag_parse(&pic, tags->user_comments[i]) >= 0) {
            opus_picture_tag_clear(&pic);
          }
        }
      }

      int binary_suffix_len;
      opus_tags_get_binary_suffix(tags, &binary_suffix_len);
    }

    if (ret == 0) {
      break;
    }
  }

  op_free(of);
  return 0;
}