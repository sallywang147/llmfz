#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pjsip.h"
#include "pjlib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize pjsip endpoint
  pj_caching_pool cp;
  pjsip_endpoint *endpt;
  pj_caching_pool_init(&cp, &pj_pool_factory_default_policy, 0);
  pj_status_t status = pjsip_endpt_create(&cp.factory, NULL, &endpt);
  if (status != PJ_SUCCESS) {
    return 0;
  }

  // Initialize pjsip module
  pjsip_module mod;
  mod.id = stream.ConsumeIntegral<int>();
  mod.priority = stream.ConsumeIntegral<int>();
  mod.name.ptr = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  mod.name.slen = stream.ConsumeIntegralInRange<int>(0, PJ_MAX_HOSTNAME);

  // Initialize pjsip_rx_data
  pjsip_rx_data rdata;
  rdata.tp_info.transport = pjsip_transport_create(endpt, PJSIP_TRANSPORT_UDP, &rdata.tp_info.rem_addr, 0);
  rdata.msg_info.msg = pjsip_msg_create(rdata.tp_info.pool, PJSIP_REQUEST_MSG);

  // Initialize pj_str_t
  pj_str_t str;
  str.ptr = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  str.slen = stream.ConsumeIntegralInRange<int>(0, PJ_MAX_HOSTNAME);

  // Initialize pjsip_hdr
  pjsip_hdr hdr;
  hdr.type = stream.ConsumeIntegral<int>();
  hdr.name.ptr = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  hdr.name.slen = stream.ConsumeIntegralInRange<int>(0, PJ_MAX_HOSTNAME);

  // Initialize pjsip_msg_body
  pjsip_msg_body body;
  body.content_type.type.ptr = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  body.content_type.type.slen = stream.ConsumeIntegralInRange<int>(0, PJ_MAX_HOSTNAME);
  body.content_type.subtype.ptr = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  body.content_type.subtype.slen = stream.ConsumeIntegralInRange<int>(0, PJ_MAX_HOSTNAME);
  body.data = const_cast<void*>(static_cast<const void*>(stream.ConsumeRandomLengthString().c_str()));
  body.len = stream.ConsumeIntegralInRange<int>(0, PJ_MAX_HOSTNAME);

  // Initialize pjsip_transaction
  pjsip_transaction *tsx;
  pjsip_tsx_create_uas(&mod, &rdata, &tsx);

  // Call the target function
  pjsip_endpt_respond(endpt, &mod, &rdata, stream.ConsumeIntegral<int>(), &str, &hdr, &body, &tsx);

  return 0;
}