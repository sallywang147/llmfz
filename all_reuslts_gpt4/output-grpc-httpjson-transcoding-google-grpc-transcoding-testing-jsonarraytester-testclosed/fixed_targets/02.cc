#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "google/grpc/transcoding/testing/json_array_tester.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRemainingBytesAsString();
  
  google::grpc::transcoding::testing::JsonArrayTester tester;
  google::grpc::transcoding::testing::JsonArrayTester::TestClosed(&tester, &str);

  return 0;
}