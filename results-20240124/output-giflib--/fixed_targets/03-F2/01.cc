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
  delete new_chunk;
  return 0;
}

extern "C" {
#include "gifProtoFuzzer.pb.cc"
}