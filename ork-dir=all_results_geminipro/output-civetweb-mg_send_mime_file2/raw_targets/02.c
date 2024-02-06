#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string path = stream.ConsumeRemainingBytesAsString();
  const std::string mime_type = stream.ConsumeRemainingBytesAsString();
  const std::string additional_headers = stream.ConsumeRemainingBytesAsString();

  struct mg_connection conn;
  mg_send_mime_file2(&conn, const_cast<char*>(path.c_str()),
                     const_cast<char*>(mime_type.c_str()),
                     const_cast<char*>(additional_headers.c_str()));
  return 0;
}