#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "resip/stack/Helper.hxx"
#include "resip/stack/SipMessage.hxx"
#include "resip/dum/DialogUsageManager.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Create a SipMessage
  resip::SipMessage* msg = new resip::SipMessage();

  // Create a Data object
  std::string str = fuzzed_data.ConsumeRandomLengthString();
  resip::Data* data_obj = new resip::Data(str.c_str());

  // Consume boolean values
  bool bool_arg1 = fuzzed_data.ConsumeBool();
  bool bool_arg2 = fuzzed_data.ConsumeBool();

  // Call the target function
  resip::Helper::makeWWWChallenge(msg, data_obj, bool_arg1, bool_arg2);

  // Clean up
  delete msg;
  delete data_obj;

  return 0;
}