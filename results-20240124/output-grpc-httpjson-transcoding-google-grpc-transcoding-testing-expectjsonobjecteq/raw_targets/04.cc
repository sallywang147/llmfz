 #include "grpc_transcoding/testing/message_test_util.h"

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

  // Generate two JSON objects.
  std::string json1 = provider.ConsumeRandomLengthString(100);
  std::string json2 = provider.ConsumeRandomLengthString(100);

  // Call the function to compare the two JSON objects.
  ExpectJsonObjectEq(&json1, &json2);

  return 0;
}
}
}
}
}
}