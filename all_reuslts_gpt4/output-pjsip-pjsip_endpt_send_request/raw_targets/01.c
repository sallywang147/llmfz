#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pjsip.h"

// Define a callback function of type func_type
void callback_func(struct pjsip_endpoint * endpt, struct pjsip_tx_data * tdata, char * token) {
    // This is a dummy function for the purpose of fuzzing.
    return;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pj_init();
    initialized = true;
  }

  struct pjsip_endpoint* endpt = pjsip_endpt_create(NULL);
  if (endpt == NULL) {
    return 0;
  }

  struct pjsip_tx_data* tdata = pjsip_endpt_create_tdata(endpt);
  if (tdata == NULL) {
    pjsip_endpt_destroy(endpt);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  int timeout = provider.ConsumeIntegral<int>();
  std::string token_str = provider.ConsumeRandomLengthString();
  char* token = const_cast<char*>(token_str.c_str());

  pjsip_endpt_send_request(endpt, tdata, timeout, token, &callback_func);

  pjsip_tx_data_dec_ref(tdata);
  pjsip_endpt_destroy(endpt);

  return 0;
}