#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_wzaes.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  mz_stream *wzaes_stream = NULL;
  int32_t written = 0;

  // Initialize wzaes stream
  mz_stream_wzaes_create(&wzaes_stream);

  // Open the stream
  mz_stream_open(wzaes_stream, NULL, MZ_OPEN_MODE_WRITE);

  // Write data to the stream
  std::string buffer = stream.ConsumeRemainingBytesAsString();
  mz_stream_wzaes_write(wzaes_stream, const_cast<char*>(buffer.c_str()), buffer.size());

  // Close the stream
  mz_stream_close(wzaes_stream);

  // Delete the stream
  mz_stream_wzaes_delete(&wzaes_stream);

  return 0;
}