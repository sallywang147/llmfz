#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pw/protobuf/stream_decoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t message = stream.ConsumeIntegral<size_t>();
  size_t table_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> table = stream.ConsumeBytes<char>(table_size);

  pw::protobuf::internal::MessageField messageField;
  size_t consumed = stream.ConsumeData(&messageField, sizeof(messageField));

  pw::protobuf::StreamDecoder decoder(reinterpret_cast<const char*>(data), size);
  decoder.Read(message, table.data(), table_size, &messageField);

  return 0;
}