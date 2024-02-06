#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

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

The fix is to remove the `const` qualifier from the `path`, `mime_type`, and `additional_headers` arguments when calling `mg_send_mime_file2`. This is because `mg_send_mime_file2` expects non-const arguments, and the compiler was complaining about the mismatch between the const and non-const arguments.