#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pw/protobuf/encoder.h"
#include "pw/protobuf/internal/message_field.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a buffer for the StreamEncoder to write into.
  std::vector<uint8_t> buffer(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  pw::protobuf::StreamEncoder encoder(buffer.data(), buffer.size());

  // Consume a size_t for the message.
  size_t message = stream.ConsumeIntegral<size_t>();

  // Consume a string for the table.
  std::string table_str = stream.ConsumeRandomLengthString();
  char* table = const_cast<char*>(table_str.c_str());

  // Create a MessageField object.
  pw::protobuf::internal::MessageField message_field;

  // Call the function to fuzz.
  encoder.Write(message, table, message_field);

  return 0;
}