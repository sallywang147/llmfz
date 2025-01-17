 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <string>

#include "ProtoToGif.h"
#include "gifProtoFuzzer.pb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gifProtoFuzzer::PlainTextExtension *extension =
      new gifProtoFuzzer::PlainTextExtension();
  gifProtoFuzzer::PlainTextExtension *from =
      new gifProtoFuzzer::PlainTextExtension();

  extension = gifProtoFuzzer::PlainTextExtension* google::protobuf::MessageLite::
      CreateMaybeMessage<gifProtoFuzzer::PlainTextExtension>(nullptr, from);
  delete extension;
  delete from;

  return 0;
}