#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "proxy_l.h"
#include "sip.h"
#include "sip_msg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string sip_msg_data = stream.ConsumeRemainingBytesAsString();
  struct sip_msg sip_msg;
  sip_msg.buf = reinterpret_cast<char*>(const_cast<char*>(sip_msg_data.c_str()));
  sip_msg.len = sip_msg_data.size();

  const std::string proxy_l_data = stream.ConsumeRemainingBytesAsString();
  struct proxy_l proxy_l;
  proxy_l.name = reinterpret_cast<char*>(const_cast<char*>(proxy_l_data.c_str()));
  proxy_l.len = proxy_l_data.size();

  return w_forward(&sip_msg, &proxy_l);
}