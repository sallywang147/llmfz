#include <stddef.h>
#include <stdint.h>

#include <FLAC/metadata.h>

extern "C" {
#include <FLAC/stream_decoder.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
  FLAC__IOCallbacks callbacks = {0};

  FLAC__metadata_chain_read_with_callbacks_(chain, (char *)data, &callbacks, 0);
  FLAC__metadata_chain_delete(chain);
  FLAC__stream_decoder_delete(decoder);

  return 0;
}