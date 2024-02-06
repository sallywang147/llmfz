#include <coap3/coap.h>
#include <stdint.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct coap_address_t addr;
  addr.addr.sin.sin_family = AF_INET;
  addr.addr.sin.sin_port = htons(stream.ConsumeIntegralInRange<uint16_t>(1, 65535));
  addr.addr.sin.sin_addr.s_addr = stream.ConsumeIntegral<uint32_t>();
  coap_new_context(&addr);
  return 0;
}