#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "protobuf-c.h"

extern "C" {
#include "oneof_field.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t field_descriptor_size = stream.ConsumeIntegral<size_t>();
  const size_t oneof_case = stream.ConsumeIntegral<int>();
  const size_t member_size = stream.ConsumeIntegral<size_t>();
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();

  struct ProtobufCFieldDescriptor field_descriptor;
  char* member = static_cast<char*>(malloc(member_size + 1));  // Added + 1 to accommodate for the null-terminator
  stream.ConsumeBytes(member, member_size);
  member[member_size] = '\0';  // Null-terminate the string
  struct ProtobufCBuffer buffer;
  char* buffer_data = static_cast<char*>(malloc(buffer_size));
  protobuf_c_buffer_init(&buffer, buffer_data, buffer_size);

  oneof_field_pack_to_buffer(&field_descriptor, oneof_case, member, &buffer);

  protobuf_c_buffer_destroy(&buffer);
  free(member);
  free(buffer_data);
  return 0;
}
```

The fix is to add a null-terminator to the `member` buffer before packing it into the Protobuf-C buffer. This is because Protobuf-C expects null-terminated strings for some of its operations, and not adding the null-terminator would lead to undefined behavior.

The line that was added to the code is:

```c++
member[member_size] = '\0';  // Null-terminate the string
```

This line adds a null-terminator to the end of the `member` buffer, ensuring that it is properly null-terminated.