#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "pw/protobuf/decoder.h"
#include "pw/protobuf/internal/decoder.h"
#include "pw/protobuf/internal/message_field.h"
#include "pw/protobuf/stream_decoder.h"
}

namespace pw {
namespace protobuf {

void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider data_provider(data, size);
  StreamDecoder decoder;
  char table[256];
  size_t table_size = data_provider.ConsumeRemainingBytes(table);
  decoder.set_field_table(table, table_size);

  while (data_provider.remaining_bytes() > 0) {
    size_t message_size = data_provider.ConsumeIntegral<size_t>();
    char message[message_size];
    data_provider.ConsumeBytes<char>(message, message_size);

    // This is the line that was missing.
    decoder.Read(message, message_size);
  }
}

}  // namespace protobuf
}  // namespace pw