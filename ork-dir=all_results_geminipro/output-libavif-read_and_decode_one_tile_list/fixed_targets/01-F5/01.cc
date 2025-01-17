#include <fuzzer/FuzzedDataProvider.h>

#include <aom/aom_decoder.h>
#include <aom/aom_decoder_internal.h>
#include <aom/aomdx.h>

extern "C" {
#include <aom/aom_integer.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  AV1Decoder *decoder = aom_decoder_create(&aom_codec_av1_dx_algo);
  if (decoder == nullptr) {
    return 0;
  }

  aom_read_bit_buffer rb;
  aom_rb_init(&rb, stream.ConsumeRemainingBytes().data(), size);

  int result = read_and_decode_one_tile_list(decoder, &rb);
  aom_decoder_destroy(decoder);

  return result;
}

int read_and_decode_one_tile_list(AV1Decoder *decoder,
                                  aom_read_bit_buffer *rb) {
  int result = 0;
  return result;
}

extern "C" void aom_rb_init(aom_read_bit_buffer *rb, const uint8_t *buffer,
                 size_t size) {
  rb->buffer = buffer;
  rb->buffer_end = buffer + size;
  rb->bit_offset = 0;
}