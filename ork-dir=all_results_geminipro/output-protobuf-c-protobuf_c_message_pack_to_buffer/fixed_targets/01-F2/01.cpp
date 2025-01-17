#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "protobuf-c.h"

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

The build issue here is that the `protobuf-c-rpc.h` header is not included, which is necessary for the `protobuf_c_message_pack_to_buffer` function. To fix this, we need to add the following line to the top of the file:

```c++
#include "protobuf-c-rpc.h"
```

We also need to wrap this header with `extern "C" {}` because it is a C header file.