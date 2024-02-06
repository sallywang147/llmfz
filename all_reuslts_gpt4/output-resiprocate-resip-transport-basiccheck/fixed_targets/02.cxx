#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rutil/Logger.hxx"
#include "resip/stack/SipMessage.hxx"
#include "resip/stack/Transport.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if(size < 1) {
    return 0;
  }

  // Initialize the logger
  resip::Log::initialize(resip::Log::Cout, resip::Log::None, nullptr);

  FuzzedDataProvider provider(data, size);

  // Create a SipMessage object
  std::string sipMessageString = provider.ConsumeRemainingBytesAsString();
  resip::Data sipData(sipMessageString.c_str());
  std::unique_ptr<resip::SipMessage> sipMessage = resip::SipMessage::make(sipData);

  // Create a Transport object
  resip::Transport* transport = nullptr;

  // Call the function under test
  bool result = resip::Transport::basicCheck(transport, sipMessage.get());

  return 0;
}