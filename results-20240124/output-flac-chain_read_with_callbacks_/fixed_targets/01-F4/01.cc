#include <fuzzer/FuzzedDataProvider.h>
#include <FLAC/metadata.h>

extern "C" {
#include <FLAC/stream_decoder.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  FLAC__IOCallbacks callbacks = {0};
  char *handle = nullptr;
  int is_ogg = 0;

  chain_read_with_callbacks_(chain, handle, &callbacks, is_ogg);

  FLAC__metadata_chain_delete(chain);

  return 0;
}