#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "pw_protobuf/stream_encoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pw::protobuf::StreamEncoder encoder;
  const size_t message_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> message(message_size);
  stream.ConsumeBytes<uint8_t>(message.data(), message_size);

  const size_t table_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> table(table_size);
  stream.ConsumeBytes<uint8_t>(table.data(), table_size);

  pw::protobuf::internal::MessageField field;
  encoder.Write(&message[0], message_size, &table[0], table_size, &field);

  return 0;
}