extern "C" {
#include <FLAC/metadata.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  FLAC__IOCallbacks callbacks = {0};
  chain_read_with_callbacks_(chain, (char *)data, &callbacks, 0);
  FLAC__metadata_chain_delete(chain);
  return 0;
}