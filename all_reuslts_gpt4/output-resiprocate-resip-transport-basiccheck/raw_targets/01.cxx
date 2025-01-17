#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rutil/Logger.hxx"
#include "resip/stack/Transport.hxx"
#include "resip/stack/SipMessage.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  resip::Log::initialize("cout", "DEBUG");

  FuzzedDataProvider provider(data, size);

  // Initialize a Transport object
  resip::Transport* transport = nullptr; // We can't instantiate an abstract class, so we pass nullptr

  // Initialize a SipMessage object
  resip::SipMessage* message = new resip::SipMessage();

  // Use the fuzzer input to populate the SipMessage
  std::string rawMessage = provider.ConsumeRemainingBytesAsString();
  message->rawWrite(rawMessage.c_str(), rawMessage.size());

  // Call the function to be fuzzed
  resip::Transport::basicCheck(transport, message);

  // Clean up
  delete message;

  return 0;
}