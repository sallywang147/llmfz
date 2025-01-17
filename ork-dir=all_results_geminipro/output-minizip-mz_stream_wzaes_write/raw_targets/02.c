#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a stream.
  void* stream_ptr = mz_stream_wzaes_create();
  if (stream_ptr == NULL) {
    return 0;
  }

  // Create a buffer.
  const size_t buf_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* buf = (char*)malloc(buf_size);
  if (buf == NULL) {
    mz_stream_wzaes_delete(&stream_ptr);
    return 0;
  }

  // Write to the stream.
  stream.ConsumeBytes(buf, buf_size);
  int result = mz_stream_wzaes_write(stream_ptr, buf, buf_size);
  if (result != MZ_OK) {
    free(buf);
    mz_stream_wzaes_delete(&stream_ptr);
    return 0;
  }

  // Close the stream.
  mz_stream_wzaes_delete(&stream_ptr);
  free(buf);

  return 0;
}