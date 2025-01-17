#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mongoose.h"

extern "C" {
#include "mongoose.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string path = stream.ConsumeRemainingBytesAsString();
  std::string mime_type = stream.ConsumeRemainingBytesAsString();
  std::string additional_headers = stream.ConsumeRemainingBytesAsString();

  struct mg_connection conn;
  mg_send_mime_file2(&conn, path.c_str(), mime_type.c_str(),
                     additional_headers.c_str());
  return 0;
}