#include <FLAC++/metadata.h>
#include <FLAC/stream_decoder.h>

extern "C" {
#include "FLAC/stream_decoder.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  FLAC__IOCallbacks callbacks = {0};
  FLAC__stream_decoder_set_read_callback(decoder, callbacks.read);
  FLAC__stream_decoder_set_seek_callback(decoder, callbacks.seek);
  FLAC__stream_decoder_set_tell_callback(decoder, callbacks.tell);
  FLAC__stream_decoder_set_eof_callback(decoder, callbacks.eof);
  FLAC__stream_decoder_set_write_callback(decoder, callbacks.write);
  FLAC__stream_decoder_set_metadata_callback(decoder, callbacks.metadata);
  FLAC__stream_decoder_set_error_callback(decoder, callbacks.error);

  FLAC__metadata_chain_read_with_callbacks(chain, (char *)data, &callbacks);

  FLAC__metadata_chain_delete(chain);
  FLAC__stream_decoder_delete(decoder);
  return 0;
}