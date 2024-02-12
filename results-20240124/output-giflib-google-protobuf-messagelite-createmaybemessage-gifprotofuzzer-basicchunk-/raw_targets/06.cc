 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "ProtoToGif.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string raw_data = stream.ConsumeRemainingBytesAsString();
  ProtoConverter converter;
  gifProtoFuzzer::BasicChunk* basic_chunk =
      converter.createBasicChunkFromRawData(raw_data);
  if (basic_chunk == nullptr) {
    return 0;
  }
  delete basic_chunk;
  return 0;
}