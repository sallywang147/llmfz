#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string path = stream.ConsumeRemainingBytesAsString();
  const std::string mime_type = stream.ConsumeRemainingBytesAsString();

  struct mg_connection conn;
  memset(&conn, 0, sizeof(conn));

  mg_send_mime_file(&conn, const_cast<char*>(path.c_str()),
                    const_cast<char*>(mime_type.c_str()));

  return 0;
}