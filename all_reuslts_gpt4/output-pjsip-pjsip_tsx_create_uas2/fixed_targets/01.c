#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pjsip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pj_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  // Create a pjsip_module
  pjsip_module tsx_user;
  tsx_user.id = provider.ConsumeRandomLengthString().c_str();
  tsx_user.priority = provider.ConsumeIntegral<int>();
  tsx_user.load = nullptr;
  tsx_user.unload = nullptr;
  tsx_user.start = nullptr;
  tsx_user.stop = nullptr;
  tsx_user.on_rx_request = nullptr;
  tsx_user.on_rx_response = nullptr;
  tsx_user.on_tx_request = nullptr;
  tsx_user.on_tx_response = nullptr;

  // Create a pjsip_rx_data
  pjsip_rx_data rdata;
  rdata.tp_info.transport = nullptr;
  rdata.tp_info.tp_data = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange(0, size)).data();
  rdata.tp_info.tp_data_len = provider.ConsumeIntegralInRange(0, size);
  rdata.tp_info.src_name = provider.ConsumeRandomLengthString().c_str();
  rdata.tp_info.src_port = provider.ConsumeIntegral<int>();
  rdata.tp_info.dst_name = provider.ConsumeRandomLengthString().c_str();
  rdata.tp_info.dst_port = provider.ConsumeIntegral<int>();

  // Create a pj_grp_lock_t
  pj_grp_lock_t grp_lock;

  // Create a pjsip_transaction
  pjsip_transaction* p_tsx = nullptr;

  // Call the function
  pjsip_tsx_create_uas2(&tsx_user, &rdata, &grp_lock, &p_tsx);

  return 0;
}