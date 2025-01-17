#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "flatbuffers/flatbuffers.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  flatbuffers::FlatBufferBuilder fbb;
  const size_t vector_size = stream.ConsumeIntegral<size_t>();
  std::vector<flatbuffers::Offset<void>> vector_data;
  for (size_t i = 0; i < vector_size; i++) {
    vector_data.push_back(fbb.CreateString(stream.ConsumeRemainingBytesAsString()));
  }
  auto vector_offset = fbb.CreateVector(vector_data);

  flatbuffers::JsonPrinter printer;
  const size_t indent = stream.ConsumeIntegral<size_t>();
  const std::string delimiter = stream.ConsumeRemainingBytesAsString();
  printer.SetIndent(indent);
  printer.SetDelimiter(delimiter.c_str());
  printer.PrintVector(vector_offset, flatbuffers::GetUByteType());

  return 0;
}