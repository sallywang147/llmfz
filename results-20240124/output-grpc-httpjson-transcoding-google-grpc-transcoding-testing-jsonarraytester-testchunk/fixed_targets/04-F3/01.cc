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

  JsonArrayTester tester;
  std::string input;
  std::string output;

  while (provider.remaining_bytes() > 0) {
    // Add a few chucks of data to the input stream.
    for (int i = 0; i < provider.ConsumeIntegralInRange(0, 5); i++) {
      input.append(provider.ConsumeRandomLengthString(100));
    }

    // Run the message reader to get the next message.
    tester.TestChunk(input, &output);

    // Handle end of input or error due to malformed bytes.
    if (tester.IsFinished()) {
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