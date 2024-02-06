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

  const std::string path = stream.ConsumeRemainingBytesAsString();
  const std::string mime_type = stream.ConsumeRemainingBytesAsString();
  const std::string additional_headers = stream.ConsumeRemainingBytesAsString();

  struct mg_connection conn;
  mg_send_mime_file2(&conn, path.c_str(), mime_type.c_str(),
                     additional_headers.c_str());
  return 0;
}
```
The fix is to remove the `const` qualifier from the `char*` arguments passed to `mg_send_mime_file2`. This is because the `mg_send_mime_file2` function expects non-const `char*` arguments, and passing const arguments will result in a compiler error.