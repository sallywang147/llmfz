#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pw/protobuf/decoder.h"
#include "pw/protobuf/internal/message_field.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize parameters for the function
  size_t message = stream.ConsumeIntegral<size_t>();
  std::string table_str = stream.ConsumeRandomLengthString();
  char* table = const_cast<char*>(table_str.c_str());
  size_t size_arg = stream.ConsumeIntegral<size_t>();
  pw::protobuf::internal::MessageField message_field;

  // Create StreamDecoder object
  pw::protobuf::StreamDecoder decoder(data, size);

  // Call the function to fuzz
  decoder.Read(message, table, size_arg, &message_field);

  return 0;
}