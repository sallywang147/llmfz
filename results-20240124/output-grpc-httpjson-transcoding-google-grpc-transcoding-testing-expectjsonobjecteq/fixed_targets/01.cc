#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "grpc_transcoding/testing/message_proto_matchers.h"
}

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Generate two JSON strings.
  std::string json_string1 = provider.ConsumeRandomLengthString(100);
  std::string json_string2 = provider.ConsumeRandomLengthString(100);

  // Call ExpectJsonObjectEq to compare the two strings.
  ExpectJsonObjectEq(&json_string1, &json_string2);

  return 0;
}
}
}
}
}
}