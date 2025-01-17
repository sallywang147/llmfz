#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gifProtoFuzzer.pb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gifProtoFuzzer::BasicChunk basic_chunk;
  gifProtoFuzzer::BasicChunk* basic_chunk_ptr = &basic_chunk;
  google::protobuf::Arena* arena = new google::protobuf::Arena();
  google::protobuf::Arena** arena_ptr = &arena;
  // Fix: missing `::` before `Construct`
  google::protobuf::Arena::InternalHelper<gifProtoFuzzer::BasicChunk>::Construct<google::protobuf::Arena*, gifProtoFuzzer::BasicChunk const&>(arena_ptr, basic_chunk_ptr, basic_chunk);
  delete arena;
  return 0;
}