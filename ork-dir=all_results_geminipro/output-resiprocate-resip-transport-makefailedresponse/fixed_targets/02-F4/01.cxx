#include "resip/resip.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  resip::Transport* transport = new resip::Transport();
  resip::SipMessage* sip_message = new resip::SipMessage();
  const int status_code = stream.ConsumeIntegral<int>();
  const std::string reason_phrase = stream.ConsumeRemainingBytesAsString();
  char* reason_phrase_cstr = new char[reason_phrase.size() + 1];
  std::strcpy(reason_phrase_cstr, reason_phrase.c_str());

  transport->makeFailedResponse(sip_message, status_code,
                                reason_phrase_cstr);
  delete[] reason_phrase_cstr;
  delete sip_message;
  delete transport;
  return 0;
}