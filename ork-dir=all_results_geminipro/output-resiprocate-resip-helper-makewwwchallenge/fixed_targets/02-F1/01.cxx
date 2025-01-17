#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "resip/resip.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string sip_message_str = stream.ConsumeRemainingBytesAsString();
  resip::SipMessage sip_message;
  sip_message.parse(sip_message_str);

  std::vector<uint8_t> data_bytes = stream.ConsumeBytes<uint8_t>(100);
  resip::Data data;
  data.assign(data_bytes.begin(), data_bytes.end());

  bool include_realm = stream.ConsumeBool();
  bool include_nonce = stream.ConsumeBool();

  resip::SipMessage *result = resip::Helper::makeWWWChallenge(&sip_message, &data,
                                                            include_realm,
                                                            include_nonce);
  delete result;
  return 0;
}