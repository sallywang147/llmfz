#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "resip/resip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  resip::SipMessage* sip_message = nullptr;
  resip::Data* data_ptr = nullptr;
  bool bool_1 = stream.ConsumeBool();
  bool bool_2 = stream.ConsumeBool();

  resip::SipMessage* result = resip::Helper::makeWWWChallenge(
      sip_message, data_ptr, bool_1, bool_2);
  delete result;
  return 0;
}