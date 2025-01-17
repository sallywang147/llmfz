#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "resip/resip.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string transport_name = stream.ConsumeRemainingBytesAsString();
  resip::Transport* transport = new resip::Transport(transport_name);
  const std::string sip_message = stream.ConsumeRemainingBytesAsString();
  resip::SipMessage* sip_msg = new resip::SipMessage(sip_message);
  const int status_code = stream.ConsumeIntegral<int>();
  const std::string reason_phrase = stream.ConsumeRemainingBytesAsString();
  transport->makeFailedResponse(transport, sip_msg, status_code,
                                reason_phrase.c_str());
  delete transport;
  delete sip_msg;
  return 0;
}