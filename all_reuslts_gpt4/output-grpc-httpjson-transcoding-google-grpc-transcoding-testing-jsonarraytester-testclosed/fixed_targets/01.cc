#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "json_array_tester.h"

using google::grpc::transcoding::testing::JsonArrayTester;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  JsonArrayTester jsonArrayTester;
  std::string str = provider.ConsumeRemainingBytesAsString();

  jsonArrayTester.TestClosed(&jsonArrayTester, &str);

  return 0;
}