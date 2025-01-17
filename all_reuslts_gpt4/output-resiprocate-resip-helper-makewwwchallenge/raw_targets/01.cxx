#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "resip/stack/Helper.hxx"
#include "resip/stack/SipMessage.hxx"
#include "resip/stack/Data.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a SipMessage object
  resip::SipMessage* sipMessage = new resip::SipMessage();

  // Create a Data object
  std::string str = stream.ConsumeRandomLengthString();
  resip::Data* dataObj = new resip::Data(str.c_str());

  // Extract boolean values
  bool bool_arg1 = stream.ConsumeBool();
  bool bool_arg2 = stream.ConsumeBool();

  // Call the function
  resip::SipMessage* result = resip::Helper::makeWWWChallenge(sipMessage, dataObj, bool_arg1, bool_arg2);

  // Clean up
  delete result;
  delete dataObj;
  delete sipMessage;

  return 0;
}