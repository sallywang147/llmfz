#include <fuzzer/FuzzedDataProvider.h>

#include <aom/aom_decoder.h>
#include <aom/aom_decoder_internal.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  AV1Decoder *decoder = aom_decoder_create(&aom_codec_av1_dx_algo);
  if (decoder == nullptr) {
    return 0;
  }

  aom_read_bit_buffer rb;
  aom_rb_init(&rb, stream.ConsumeRemainingBytes().data(), size);

  char *buffer = nullptr;
  char *buffer_end = nullptr;
  char **buffer_ptr = &buffer;
  int buffer_size = 0;

  int result = read_and_decode_one_tile_list(decoder, &rb, buffer, buffer_end,
                                             buffer_ptr, &buffer_size);
  aom_decoder_destroy(decoder);

  return result;
}