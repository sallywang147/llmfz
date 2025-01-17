#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rutil/Logger.hxx"
#include "resip/stack/Transport.hxx"
#include "resip/stack/SipMessage.hxx"

using namespace resip;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    Log::initialize(Log::Cout, Log::None, nullptr);
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // We don't have a real Transport to use, so we just pass nullptr.
  Transport* transport = nullptr;

  // Create a SipMessage. This could be more sophisticated, e.g. by actually
  // parsing some of the input data into a SipMessage, but this is a simple
  // starting point.
  auto sipMessage = std::make_unique<SipMessage>();

  // Get an int from the data.
  int int_arg = stream.ConsumeIntegral<int>();

  // Get a string from the data. We ensure it's null-terminated by adding a
  // null byte at the end.
  std::string str_arg = stream.ConsumeRemainingBytesAsString();
  str_arg.push_back('\0');

  // Call the function under test.
  Transport::makeFailedResponse(transport, sipMessage.get(), int_arg, &str_arg[0]);

  return 0;
}