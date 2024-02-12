#include <stddef.h>
#include <stdint.h>
extern "C" {
#include <FLAC/metadata.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  if (chain == NULL) {
    return 0;
  }
  FLAC__IOCallbacks callbacks = {0};
  FLAC__metadata_chain_read_with_callbacks(chain, (char *)data, &callbacks);
  FLAC__metadata_chain_delete(chain);
  return 0;
}