#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <vector>

#include "class/net/net_device.h"
#include "fuzz/fuzz.h"
#include "tusb.h"

extern "C" {

#define FUZZ_ITERATIONS 500

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

void net_task(FuzzedDataProvider *provider);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider provider(Data, Size);
  std::vector<uint8_t> callback_data = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, Size));
  fuzz_init(callback_data.data(), callback_data.size());
  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);

  for (int i = 0; i < FUZZ_ITERATIONS; i++) {
    if (provider.remaining_bytes() == 0) {
      return 0;
    }
    tud_int_handler(provider.ConsumeIntegral<uint8_t>());
    tud_task(); // tinyusb device task
    net_task(&provider);
  }

  return 0;
}

//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+
enum NetApiFuncs {
  kNetworkRecvRenew,
  kNetworkCanXmit,
  kNetworkXmit,
  kMaxValue,
};

void net_task(FuzzedDataProvider *provider) {

  assert(provider != NULL);
  switch (provider->ConsumeEnum<NetApiFuncs>()) {

  case kNetworkRecvRenew:
    tud_network_recv_renew();
    break;
  case kNetworkCanXmit:
    (void)tud_network_can_xmit(provider->ConsumeIntegral<uint16_t>());
    break;
  case kNetworkXmit:
    // TODO: Actually pass real values here later.
    tud_network_xmit(provider->ConsumeBytes<uint8_t>(provider->ConsumeIntegralInRange<size_t>(0, Size)).data(),
                     provider->ConsumeIntegralInRange<size_t>(0, Size));
    break;

  case kMaxValue:
    // Noop.
    break;
  }
}

bool netd_control_xfer_cb(char rhport, char ep_addr, struct tusb_control_request_t *request) {
  // TODO: Actually implement this function.
  (void)rhport;
  (void)ep_addr;
  (void)request;
  return false;
}
}