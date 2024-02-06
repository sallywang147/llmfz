#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mz_strm.h"
#include "mz_strm_wzaes.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  mz_stream *wzaes_stream = nullptr;
  int32_t status = MZ_OK;

  // Initialize the stream
  mz_stream_wzaes_create(&wzaes_stream);

  // Open the stream
  status = mz_stream_open(wzaes_stream, NULL, MZ_OPEN_MODE_WRITE);
  if (status != MZ_OK) {
    mz_stream_delete(&wzaes_stream);
    return 0;
  }

  // Get the buffer from the fuzzer
  std::string buffer = stream.ConsumeRemainingBytesAsString();
  char* buf = const_cast<char*>(buffer.c_str());

  // Write to the stream
  mz_stream_wzaes_write(wzaes_stream, buf, buffer.size());

  // Close the stream
  mz_stream_close(wzaes_stream);

  // Delete the stream
  mz_stream_delete(&wzaes_stream);

  return 0;
}