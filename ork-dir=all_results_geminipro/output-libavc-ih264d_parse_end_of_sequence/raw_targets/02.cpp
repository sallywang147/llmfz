#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ih264d_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _DecStruct dec_struct;
  ih264d_init(&dec_struct);

  while (stream.remaining_bytes() > 0) {
    const size_t next_size = stream.ConsumeIntegralInRange<size_t>(
        0, stream.remaining_bytes());
    auto next_input = stream.ConsumeBytes<uint8_t>(next_size);
    ih264d_decode_video_buffer(&dec_struct, next_input.data(), next_input.size());
  }

  ih264d_parse_end_of_sequence(&dec_struct);
  ih264d_release(&dec_struct);

  return 0;
}