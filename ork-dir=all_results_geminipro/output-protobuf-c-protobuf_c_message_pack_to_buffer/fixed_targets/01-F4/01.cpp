#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "protobuf-c.h"
#include "protobuf-c-rpc.h"

extern "C" {
#include "protobuf-c-rpc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string message_name = stream.ConsumeRemainingBytesAsString();

  ProtobufCMessage* message = protobuf_c_message_new(message_name.c_str());
  if (message == nullptr) {
    return 0;
  }

  ProtobufCBuffer buffer;
  protobuf_c_buffer_init(&buffer, 0, nullptr);

  size_t packed_size = protobuf_c_message_pack_to_buffer(message, &buffer);
  if (packed_size == 0) {
    protobuf_c_message_free_unpacked(message, nullptr);
    protobuf_c_buffer_destroy(&buffer);
    return 0;
  }

  protobuf_c_message_free_unpacked(message, nullptr);
  protobuf_c_buffer_destroy(&buffer);
  return 0;
}
```

The original code has a build issue because the header file `protobuf-c-rpc.h` is included twice, once with `#include` and once with `extern "C" { #include }`. This causes a compiler error because the header file is defined twice. To fix this, remove the second inclusion of `protobuf-c-rpc.h` with `extern "C" { #include }`.