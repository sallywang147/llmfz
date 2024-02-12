#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <string>

#include "ProtoToGif.h"
#include "gifProtoFuzzer.pb.h"

extern "C" {
#include <google/protobuf/message_lite.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gifProtoFuzzer::PlainTextExtension *extension =
      gifProtoFuzzer::PlainTextExtension* google::protobuf::MessageLite::
      CreateMaybeMessage<gifProtoFuzzer::PlainTextExtension>(nullptr, nullptr);
  gifProtoFuzzer::PlainTextExtension *from =
      new gifProtoFuzzer::PlainTextExtension();

  extension->ParseFromZeroCopyStream(&stream);
  delete extension;
  delete from;

  return 0;
}