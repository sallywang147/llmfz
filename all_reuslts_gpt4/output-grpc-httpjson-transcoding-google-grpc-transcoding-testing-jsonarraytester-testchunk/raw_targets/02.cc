#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "google/grpc/transcoding/testing/json_array_tester.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  google::grpc::transcoding::testing::JsonArrayTester tester;
  std::string input = stream.ConsumeRandomLengthString();
  std::string output;
  bool is_final = stream.ConsumeBool();

  tester.TestChunk(&tester, &input, &output, is_final);

  return 0;
}