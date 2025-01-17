#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "gifProtoFuzzer.pb.h"

using namespace gifProtoFuzzer;

extern "C" {
#include <google/protobuf/message_lite.h>
}

DEFINE_PROTO_FUZZER(const BasicChunk &chunk) {
  BasicChunk *new_chunk = BasicChunk::CreateMaybeMessage<BasicChunk>(nullptr, &chunk);
  delete new_chunk;
}