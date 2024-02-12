#include "grpc_transcoding/testing/json_array_tester.h"

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

  JsonArrayTester tester;
  std::string chunk;
  std::string error;

  while (provider.remaining_bytes() > 0) {
    // Add a few chucks of data to the input stream.
    for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
      chunk = provider.ConsumeRandomLengthString(100);
      if (!tester.TestChunk(&chunk, &error, false)) {
        return 0;
      }
    }
  }

  return 0;
}
}
}
}
}
}