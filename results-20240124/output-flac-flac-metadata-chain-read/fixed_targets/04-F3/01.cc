#include <stddef.h>
#include <stdint.h>

#include "FLAC++/metadata.h"

extern "C" {
#include "FLAC/stream_decoder.h"
}

static FLAC__StreamDecoder *decoder;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  bool ok = FLAC__metadata_chain_read(decoder->metadata, (char *)data, decoder->io_callbacks, false);
  return 0;
}