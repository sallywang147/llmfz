#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "pw_protobuf/stream_encoder.h"

extern "C" {
#include "pw_protobuf/stream_encoder.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t message = stream.ConsumeIntegral<size_t>();
  const size_t table_size = stream.ConsumeIntegral<size_t>();
  char* table = static_cast<char*>(std::malloc(table_size));
  stream.ConsumeBytes(table, table_size);
  pw::protobuf::StreamEncoder encoder;
  pw::protobuf::internal::MessageField field;
  encoder.WriteMessage(&message, table, table_size, &field);
  std::free(table);
  return 0;
}
```

The fix is to wrap the `#include "pw_protobuf/stream_encoder.h"` with `extern "C" {}` to allow the object linking to succeed.