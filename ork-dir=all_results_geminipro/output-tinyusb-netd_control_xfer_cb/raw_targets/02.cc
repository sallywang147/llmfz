#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

#include "class/net/net_device.h"
#include "fuzz/fuzz.h"
#include "tusb.h"
#include <cstdint>
#include <string>
#include <vector>

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
  kControlXferCb,
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
  case kNetworkXmit:
    // TODO: Actually pass real values here later.
    tud_network_xmit(NULL, 0);
  case kControlXferCb:
    {
      struct tusb_control_request_t ctrl_req;
      ctrl_req.bRequestType = provider->ConsumeIntegral<uint8_t>();
      ctrl_req.bRequest = provider->ConsumeIntegral<uint8_t>();
      ctrl_req.wValue = provider->ConsumeIntegral<uint16_t>();
      ctrl_req.wIndex = provider->ConsumeIntegral<uint16_t>();
      ctrl_req.wLength = provider->ConsumeIntegral<uint16_t>();
      netd_control_xfer_cb(0, 0, &ctrl_req);
    }
  case kMaxValue:
    // Noop.
    break;
  }
}
}