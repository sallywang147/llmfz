#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class/msc/msc_device.h"
#include "fuzz/fuzz.h"
#include "tusb.h"

extern "C" {

#define FUZZ_ITERATIONS 500

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

void msc_task(FuzzedDataProvider *provider);

bool mscd_xfer_cb(char lun, char ep_addr, int dir, int len);

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
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
    msc_task(&provider);
  }

  return 0;
}

//--------------------------------------------------------------------+
// USB MSC
//--------------------------------------------------------------------+

void msc_task(FuzzedDataProvider *provider) {

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

  case kMaxValue:
    // Noop.
    break;
  }

  // Call the function that was not called by the fuzz target.
  mscd_xfer_cb(0, 0, 0, 0);
}
}