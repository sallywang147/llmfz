#include <fuzzer/FuzzedDataProvider.h>
#include <lwip/udp.h>
#include <lwip/ip4_addr.h>
#include <lwip/pbuf.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, provider.ConsumeIntegralInRange<uint16_t>(0, 1024), PBUF_RAM);
  if (p == NULL) {
    return 0;
  }
  provider.ConsumeBytes(p->payload, p->len);
  struct udp_pcb *pcb = udp_new();
  if (pcb == NULL) {
    pbuf_free(p);
    return 0;
  }
  struct ip4_addr addr;
  IP4_ADDR(&addr, provider.ConsumeIntegralInRange<uint8_t>(0, 255), provider.ConsumeIntegralInRange<uint8_t>(0, 255),
           provider.ConsumeIntegralInRange<uint8_t>(0, 255), provider.ConsumeIntegralInRange<uint8_t>(0, 255));
  udp_recv_proc((char *)p->payload, pcb, p, &addr, provider.ConsumeIntegralInRange<uint16_t>(0, 65535));
  udp_remove(pcb);
  pbuf_free(p);
  return 0;
}