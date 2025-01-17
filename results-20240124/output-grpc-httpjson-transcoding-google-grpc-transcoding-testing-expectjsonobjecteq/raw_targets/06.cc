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

  std::string json_1 = provider.ConsumeRandomLengthString(100);
  std::string json_2 = provider.ConsumeRandomLengthString(100);

  ExpectJsonObjectEq(&json_1, &json_2);

  return 0;
}
}
}
}
}
}