#include <fuzzer/FuzzedDataProvider.h>
#include <aom/aom_decoder.h>
#include <aom/aomdx.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  aom_codec_ctx_t codec;
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), nullptr, 0)) {
    return 0;
  }

  aom_codec_iter_t iter = nullptr;
  aom_image_t *img = nullptr;

  if (aom_codec_decode(&codec, data, size, nullptr)) {
    aom_codec_destroy(&codec);
    return 0;
  }

  while ((img = aom_codec_get_frame(&codec, &iter)) != nullptr) {
    // Consume the image data.
  }

  struct AV1Decoder *pbi = static_cast<struct AV1Decoder *>(codec.priv);
  struct aom_read_bit_buffer rb = {0};
  int tile_size_bytes = stream.ConsumeIntegral<int>();
  char *data_end = const_cast<char *>(reinterpret_cast<const char *>(stream.ConsumeRemainingBytes().data()));
  char *saved_buf = const_cast<char *>(reinterpret_cast<const char *>(stream.ConsumeRemainingBytes().data()));
  char **buf = &saved_buf;
  int *bytes_read = new int(0);
  int frame_size_override_flag = stream.ConsumeIntegral<int>();

  read_one_tile_group_obu(pbi, &rb, tile_size_bytes, data_end, saved_buf, buf, bytes_read, frame_size_override_flag);

  delete bytes_read;
  aom_codec_destroy(&codec);

  return 0;
}