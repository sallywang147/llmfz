#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "grpc_transcoding/testing/json_array_tester.h"
#include "test_common.h"

namespace google {
namespace grpc {
namespace transcoding {
namespace testing {
namespace {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  TestZeroCopyInputStream input_stream;
  JsonArrayTester tester(&input_stream);

  while (provider.remaining_bytes() > 0) {
    // Add a few chucks of data to the input stream.
    for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
      input_stream.AddChunk(provider.ConsumeRandomLengthString(100));
    }

    // Run the json array tester to get the next message.
    std::string error_message;
    if (tester.TestClosed(&error_message)) {
      return 0;
    }
  }

  return 0;
}
}
}
}
}
}