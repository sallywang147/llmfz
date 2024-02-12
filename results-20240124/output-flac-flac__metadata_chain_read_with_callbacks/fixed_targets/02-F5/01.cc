#include <FLAC/metadata.h>
#include <FLAC/stream_decoder.h>

extern "C" {
#include <FLAC/metadata_chain.h>
}

int main() {
  FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  FLAC__metadata_chain_read_with_callbacks(chain, decoder, FLAC__metadata_callbacks_read, FLAC__metadata_callbacks_seek, FLAC__metadata_callbacks_tell, FLAC__metadata_callbacks_eof, FLAC__metadata_callbacks_write, FLAC__metadata_callbacks_metadata, FLAC__metadata_callbacks_error, FLAC__metadata_callbacks_data);
  FLAC__metadata_chain_delete(chain);
  FLAC__stream_decoder_delete(decoder);
  return 0;
}