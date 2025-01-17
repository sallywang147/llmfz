#include <pjsip/sip_message.h>
#include <pjlib-util.h>
#include <pjlib.h>
#include <pjsip.h>
#include <pjsip_ua.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <pjsip/sip_message.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize pjsip
  pj_status_t status;
  pj_caching_pool cp;
  pj_pool_factory *pf;
  pj_thread_desc main_thread;
  pj_thread_t *thread = &main_thread;

  pj_init();
  pj_caching_pool_init(&cp, &pj_system_allocator, 0);
  pf = pj_pool_factory_default();
  status = pj_thread_create(thread, "main", NULL, thread, 0, 0);

  // Create pjsip_module
  pjsip_module mod;
  pjsip_module_init(&mod, NULL);

  // Create pjsip_rx_data
  pjsip_rx_data rdata;
  pjsip_rx_data_init(&rdata);
  rdata.msg_info.type = PJSIP_REQUEST_MSG;
  rdata.msg_info.method = stream.ConsumeIntegral<pjsip_method>();
  rdata.msg_info.status_code = stream.ConsumeIntegral<pjsip_status_code>();
  rdata.msg_info.cseq = stream.ConsumeIntegral<pj_uint32_t>();
  rdata.msg_info.call_id = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024)).c_str();
  rdata.msg_info.to = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024)).c_str();
  rdata.msg_info.from = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024)).c_str();

  // Create pjsip_transaction
  pjsip_transaction *tsx = NULL;

  // Call pjsip_tsx_create_uas
  status = pjsip_tsx_create_uas(&mod, &rdata, &tsx);

  // Cleanup
  pjsip_rx_data_deinit(&rdata);
  pjsip_module_deinit(&mod);
  pj_thread_join(thread);
  pj_caching_pool_deinit(&cp);
  pj_shutdown();

  return 0;
}