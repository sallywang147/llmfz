...
#include "FLAC/metadata.h"
#include "FLAC/stream_decoder.h"
...
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
...
	FLAC__IOCallbacks io_callbacks;
	io_callbacks.read = read_callback;
	io_callbacks.seek = seek_callback;
	io_callbacks.tell = tell_callback;
	io_callbacks.write = write_callback;
	io_callbacks.close = close_callback;
	FLAC__Metadata_Chain * chain = FLAC__metadata_chain_new();
	FLAC__metadata_chain_read_with_callbacks(chain, filename, &io_callbacks);
...
}