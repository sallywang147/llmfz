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
  callbacks.read = FLAC__IOCallbacks_read_callback_null;
  callbacks.seek = FLAC__IOCallbacks_seek_callback_null;
  callbacks.tell = FLAC__IOCallbacks_tell_callback_null;
  callbacks.write = FLAC__IOCallbacks_write_callback_null;
  callbacks.close = FLAC__IOCallbacks_close_callback_null;
  FLAC__metadata_chain_read_with_callbacks(chain, (char *)data, &callbacks);
  FLAC__metadata_chain_delete(chain);
  return 0;
}