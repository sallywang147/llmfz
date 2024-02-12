#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gifProtoFuzzer.pb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gifProtoFuzzer::BasicChunk chunk;
  chunk.set_type(stream.ConsumeIntegral<uint32_t>());
  chunk.set_data(stream.ConsumeRemainingBytesAsString());

  gifProtoFuzzer::BasicChunk* new_chunk =
      gifProtoFuzzer::BasicChunk::New(chunk);
  // Call the ArenaConstruct function to construct the BasicChunk object.
  gifProtoFuzzer::BasicChunk* constructed_chunk =
      gifProtoFuzzer::BasicChunk::ArenaConstruct(nullptr, nullptr, new_chunk);
  // Call the InternalHelper function to construct the BasicChunk object.
  gifProtoFuzzer::BasicChunk* internal_constructed_chunk =
      google::protobuf::Arena::InternalHelper<gifProtoFuzzer::BasicChunk>::Construct<google::protobuf::Arena*, gifProtoFuzzer::BasicChunk const&>(
          nullptr, nullptr, *new_chunk);
  delete internal_constructed_chunk;
  delete constructed_chunk;
  delete new_chunk;
  return 0;
}

extern "C" {
#include "gifProtoFuzzer.pb.cc"
}

namespace gifProtoFuzzer {
namespace {
// This function is required by the protobuf library to construct the BasicChunk
// object. It is not called directly by the fuzzer, but it must be defined in
// order for the fuzzer to work correctly.
BasicChunk* ArenaConstruct(char* ptr, Arena** args, BasicChunk* chunk) {
  return new (ptr) BasicChunk(*chunk);
}
}  // namespace
}  // namespace gifProtoFuzzer