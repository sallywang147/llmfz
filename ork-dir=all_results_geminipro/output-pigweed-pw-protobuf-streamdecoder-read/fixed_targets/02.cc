#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "pw/protobuf/decoder.h"
#include "pw/protobuf/internal/message_field.h"
#include "pw/protobuf/stream_decoder.h"

extern "C" {
#include "pw_protobuf_stream_decoder_fuzzer_test.pb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t message = stream.ConsumeIntegral<size_t>();
  const size_t table_size = stream.ConsumeIntegral<size_t>();
  char* table = new char[table_size];
  stream.ConsumeBytes(table, table_size);
  pw::protobuf::internal::MessageField field;
  pw::protobuf::StreamDecoder decoder;
  int result = decoder.Read(&decoder, message, table, table_size, &field);
  delete[] table;
  return result;
}