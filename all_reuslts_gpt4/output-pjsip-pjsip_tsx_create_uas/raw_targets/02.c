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

  // Initialize pjsip_module
  pjsip_module module = {
    NULL, NULL,                          /* prev, next.      */
    {NULL, 0},                           /* Name.            */
    -1,                                  /* Id               */
    PJSIP_MOD_PRIORITY_TRANSPORT_LAYER,  /* Priority         */
    NULL,                                /* load()           */
    NULL,                                /* start()          */
    NULL,                                /* stop()           */
    NULL,                                /* unload()         */
    NULL,                                /* on_rx_request()  */
    NULL,                                /* on_rx_response() */
    NULL,                                /* on_tx_request.   */
    NULL,                                /* on_tx_response() */
    NULL,                                /* on_tsx_state()   */
  };

  // Initialize pjsip_rx_data
  pjsip_rx_data rdata;
  pj_bzero(&rdata, sizeof(rdata));
  rdata.tp_info.transport = NULL;
  rdata.tp_info.pool = pj_pool_create(&pj_get_default_caching_pool()->factory, "rdata", 4000, 4000, NULL);
  rdata.msg_info.msg_buf = (char*)provider.ConsumeBytes<uint8_t>(size).data();
  rdata.msg_info.len = size;
  rdata.pkt_info.packet = rdata.msg_info.msg_buf;
  rdata.pkt_info.len = rdata.msg_info.len;

  // Initialize pjsip_transaction
  pjsip_transaction* tsx = NULL;

  // Call the target function
  pjsip_tsx_create_uas(&module, &rdata, &tsx);

  // Cleanup
  pj_pool_release(rdata.tp_info.pool);

  return 0;
}