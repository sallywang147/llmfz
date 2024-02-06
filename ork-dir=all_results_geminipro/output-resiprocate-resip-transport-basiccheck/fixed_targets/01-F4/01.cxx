#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>

#include "resip/sip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  resip::Transport transport;
  resip::SipMessage message;

  const std::string method = stream.ConsumeRandomLengthString();
  const std::string uri = stream.ConsumeRandomLengthString();
  const std::string version = stream.ConsumeRandomLengthString();
  message.setMethod(method);
  message.setUri(uri);
  message.setVersion(version);

  const std::string header_name = stream.ConsumeRandomLengthString();
  const std::string header_value = stream.ConsumeRandomLengthString();
  message.addHeader(header_name, header_value);

  const std::string body = stream.ConsumeRandomLengthString();
  message.setBody(body);

  // Check the message before sending it.
  if (!message.check()) {
    return 0;
  }

  // Pass the correct arguments to transport.basicCheck().
  transport.basicCheck(&message);
  return 0;
}