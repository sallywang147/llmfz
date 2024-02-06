#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "resip/stack/transport.h"

extern "C" {
#include "resip/stack/sip_message.h"
#include "resip/stack/sip_parser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t transport_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  resip::Transport* transport = new resip::Transport(transport_size);
  const size_t sip_message_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  resip::SipMessage* sip_message = new resip::SipMessage(sip_message_size);

  const std::string sip_data = stream.ConsumeRemainingBytesAsString();
  resip::SipParser::parse(sip_message, sip_data.c_str(), sip_data.size());

  bool result = transport->basicCheck(transport, sip_message);

  delete sip_message;
  delete transport;
  return 0;
}