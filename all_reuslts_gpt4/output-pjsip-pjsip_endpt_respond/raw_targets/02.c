#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pjsip.h"
#include "pjlib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pj_init();
    initialized = true;
  }
  
  FuzzedDataProvider stream(data, size);

  // Initialize endpoint
  pj_caching_pool cp;
  pj_caching_pool_init(&cp, NULL, 0);
  pjsip_endpoint *endpt;
  pj_status_t status = pjsip_endpt_create(&cp.factory, "fuzz", &endpt);
  if (status != PJ_SUCCESS) {
    return 0;
  }

  // Initialize module
  pjsip_module module;
  module.id = stream.ConsumeRandomLengthString().c_str();
  module.priority = stream.ConsumeIntegral<int>();

  // Initialize rx_data
  pjsip_rx_data rdata;
  rdata.tp_info.transport = NULL;
  rdata.tp_info.tp_data = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();

  // Initialize st_code
  int st_code = stream.ConsumeIntegral<int>();

  // Initialize st_text
  pj_str_t st_text;
  st_text.ptr = stream.ConsumeRandomLengthString().c_str();
  st_text.slen = stream.ConsumeIntegral<int>();

  // Initialize hdr_list
  pjsip_hdr hdr_list;
  hdr_list.name = stream.ConsumeRandomLengthString().c_str();
  hdr_list.sname = stream.ConsumeRandomLengthString().c_str();

  // Initialize msg_body
  pjsip_msg_body body;
  body.content_type.type = stream.ConsumeRandomLengthString().c_str();
  body.content_type.subtype = stream.ConsumeRandomLengthString().c_str();
  body.data = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();
  body.len = stream.ConsumeIntegral<int>();

  // Initialize p_tsx
  pjsip_transaction *p_tsx = NULL;

  // Call the function
  pjsip_endpt_respond(endpt, &module, &rdata, st_code, &st_text, &hdr_list, &body, &p_tsx);

  // Cleanup
  pjsip_endpt_destroy(endpt);
  pj_caching_pool_destroy(&cp);

  return 0;
}