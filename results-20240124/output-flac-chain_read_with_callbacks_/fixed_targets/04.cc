#include <FLAC/stream_decoder.h>
#include <FLAC/metadata.h>

extern "C" {
#include <FLAC/stream_decoder.h>
#include <FLAC/metadata.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  FLAC__IOCallbacks callbacks = {0};
  if(!chain.read_with_callbacks_(filename, ogg))
    return 0;
  FLAC__metadata_chain_delete(chain);
  return 0;
}