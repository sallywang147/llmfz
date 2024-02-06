#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pjsip.h"

// Define a callback function that matches the func_type signature
void cb_func(pjsip_endpoint *endpt, pjsip_tx_data *tdata, int timeout, char *token) {
    // Do nothing in the callback
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pj_init();
    initialized = true;
  }
  
  pjsip_endpoint *endpt = NULL;
  pjsip_tx_data *tdata = NULL;
  int ret;
  
  // Initialize endpoint and transaction data
  ret = pjsip_endpt_create(&endpt);
  if (ret != PJ_SUCCESS) {
    return 0;
  }
  
  ret = pjsip_endpt_create_tdata(endpt, &tdata);
  if (ret != PJ_SUCCESS) {
    pjsip_endpt_destroy(endpt);
    return 0;
  }
  
  FuzzedDataProvider provider(data, size);
  
  // Consume data for timeout and token
  int timeout = provider.ConsumeIntegral<int>();
  std::string token = provider.ConsumeRandomLengthString();
  
  // Call the target function
  pjsip_endpt_send_request(endpt, tdata, timeout, const_cast<char*>(token.c_str()), &cb_func);
  
  // Clean up
  pjsip_tx_data_dec_ref(tdata);
  pjsip_endpt_destroy(endpt);

  return 0;
}