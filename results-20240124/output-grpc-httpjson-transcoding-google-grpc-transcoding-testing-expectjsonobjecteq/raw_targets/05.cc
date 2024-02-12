 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "grpc_transcoding/testing/message_test_util.h"

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string json_a = provider.ConsumeRandomLengthString(1000);
  std::string json_b = provider.ConsumeRandomLengthString(1000);

  (void)ExpectJsonObjectEq(&json_a, &json_b);

  return 0;
}
}
}
}
}
}