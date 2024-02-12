#include <FLAC/metadata.h>
#include <FLAC/stream_decoder.h>

extern "C" {
#include <FLAC/export.h>
}

int main() {
  FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
  FLAC__StreamDecoderInitStatus init_status = FLAC__stream_decoder_init_stream(decoder, read_callback, seek_callback, tell_callback, length_callback, eof_callback, write_callback, metadata_callback, error_callback, client_data);
  if (init_status != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
    // Handle error
    return 1;
  }

  FLAC__bool metadata_read = FLAC__metadata_chain_read_with_callbacks(decoder, read_metadata_callback, tell_metadata_callback, length_metadata_callback, eof_metadata_callback, client_data);
  if (!metadata_read) {
    // Handle error
    return 1;
  }

  // Decode and process audio data

  FLAC__stream_decoder_finish(decoder);
  FLAC__stream_decoder_delete(decoder);

  return 0;
}