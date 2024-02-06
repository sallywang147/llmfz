#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "google/grpc/transcoding/testing/json_test_utils.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string str1 = provider.ConsumeRandomLengthString();
  std::string str2 = provider.ConsumeRemainingBytesAsString();

  google::grpc::transcoding::testing::ExpectJsonArrayEq(&str1, &str2);

  return 0;
}