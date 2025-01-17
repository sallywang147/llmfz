#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "pw/protobuf/stream_decoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pw::protobuf::StreamDecoder decoder;
  const size_t message_size = stream.ConsumeIntegral<size_t>();
  const size_t table_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> table(table_size);
  stream.ConsumeBytes<char>(table_size, table.data());

  pw::protobuf::internal::MessageField message_field;
  const int result = decoder.Read(&decoder, message_size, table.data(), table_size,
                                 &message_field);
  return result;
}