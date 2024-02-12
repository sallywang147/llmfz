#include "grpc_transcoding/message_reader.h"

#include "test_common.h"

#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string json_expected = provider.ConsumeRemainingBytesAsString();
  std::string json_actual = provider.ConsumeRemainingBytesAsString();

  // Call the function under test.
  bool result = ExpectJsonObjectEq(json_expected, json_actual);

  return 0;
}
}
}
}
}
}