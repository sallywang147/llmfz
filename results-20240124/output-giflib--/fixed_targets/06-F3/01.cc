#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gifProtoFuzzer.pb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gifProtoFuzzer::BasicChunk chunk;
  stream.ConsumeData(&chunk, sizeof(chunk));
  gifProtoFuzzer::BasicChunk* ptr =
      google::protobuf::Arena::InternalHelper<gifProtoFuzzer::BasicChunk>::Construct<
          google::protobuf::Arena*, gifProtoFuzzer::BasicChunk const&>(
              nullptr, nullptr, &chunk);
  if (ptr == nullptr) {
    return 0;
  }
  // Do something with ptr.
  return 0;
}