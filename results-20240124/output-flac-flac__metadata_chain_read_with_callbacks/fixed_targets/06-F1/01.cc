#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

extern "C" {
#include "FLAC++/metadata.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  if (!chain) {
    return 0;
  }

  struct FLAC__IOCallbacks io_callbacks = {
    .read = [](void *client_data, FLAC__uint64 offset, void *buffer,
               size_t bytes) -> FLAC__StreamDecoderReadStatus {
      FuzzedDataProvider *stream =
          reinterpret_cast<FuzzedDataProvider *>(client_data);
      const uint8_t *input = stream->ConsumeBytes<uint8_t>(bytes);
      memcpy(buffer, input, bytes);
      return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
    },
    .seek = [](void *client_data, FLAC__uint64 absolute_byte_offset)
        -> FLAC__StreamDecoderSeekStatus {
      return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
    },
    .tell = [](void *client_data) -> FLAC__uint64 { return 0; },
    .eof = [](void *client_data) -> FLAC__bool { return false; },
    .write = [](void *client_data, const FLAC__int32 *buffer, size_t samples,
                unsigned channels, unsigned bits_per_sample,
                const FLAC__ChannelAssignment *channel_assignment)
        -> FLAC__StreamEncoderWriteStatus {
      return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
    },
    .metadata = [](void *client_data, const FLAC__StreamMetadata *metadata)
        -> void {}
  };

  FLAC__metadata_chain_read_with_callbacks(chain, nullptr, &io_callbacks);
  FLAC__metadata_chain_delete(chain);
  return 0;
}