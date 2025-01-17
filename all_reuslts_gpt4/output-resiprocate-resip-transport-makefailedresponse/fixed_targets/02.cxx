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
  static bool initialized = false;
  if (!initialized) {
    resip::Log::initialize(resip::Log::Cout, resip::Log::None, "fuzzer");
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  resip::Transport* transport = nullptr;
  resip::SipMessage* message = resip::SipMessage::makeEmptySipMessage();

  int code = provider.ConsumeIntegral<int>();
  std::string reason = provider.ConsumeRemainingBytesAsString();
  char* reasonPtr = const_cast<char*>(reason.c_str());

  resip::Transport::makeFailedResponse(transport, message, code, reasonPtr);

  delete message;

  return 0;
}