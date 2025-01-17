#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "pw/protobuf/encoder.h"
#include "pw/protobuf/internal/message_field.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract values
  size_t message = stream.ConsumeIntegral<size_t>();
  std::string table = stream.ConsumeRandomLengthString();
  size_t table_size = table.size();
  pw::protobuf::internal::MessageField message_field;

  // Create StreamEncoder
  std::array<uint8_t, 256> buffer;
  pw::protobuf::StreamEncoder encoder(buffer);

  // Call the function to fuzz
  encoder.Write(message, table.c_str(), table_size, &message_field);

  return 0;
}