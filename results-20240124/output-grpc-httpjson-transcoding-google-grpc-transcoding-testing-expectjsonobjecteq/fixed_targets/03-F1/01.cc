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

  // Generate two JSON strings.
  std::string json1 = provider.ConsumeRandomLengthString(100);
  std::string json2 = provider.ConsumeRandomLengthString(100);

  // Call the function to compare the JSON strings.
  bool result = ExpectJsonObjectEq(json1, json2);

  // Handle the result.
  if (result) {
    // The JSON strings are equal.
    return 0;
  } else {
    // The JSON strings are not equal.
    return 1;
  }
}
}
}
}
}
}