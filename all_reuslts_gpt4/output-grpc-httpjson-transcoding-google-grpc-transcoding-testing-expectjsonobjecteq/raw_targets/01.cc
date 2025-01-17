#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "google/grpc/transcoding/testing/json_match.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  google::grpc::transcoding::testing::ExpectJsonObjectEq(&str1, &str2);

  return 0;
}