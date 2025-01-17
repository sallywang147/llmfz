#include <fuzzer/FuzzedDataProvider.h>
#include <pjsip.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize pjsip
  pj_init();
  pjsip_endpt_create(&cp.factory, "fuzzer", &endpt);

  // Create and initialize tsx_user
  pjsip_module tsx_user;
  tsx_user.id = stream.ConsumeIntegral<int>();
  tsx_user.priority = stream.ConsumeIntegral<int>();
  tsx_user.on_tsx_state = NULL;
  tsx_user.on_rx_request = NULL;
  tsx_user.on_rx_response = NULL;
  tsx_user.on_tx_request = NULL;
  tsx_user.on_tx_response = NULL;
  tsx_user.on_tsx_user = NULL;

  // Create and initialize rdata
  pjsip_rx_data rdata;
  rdata.tp_info.transport = NULL;
  rdata.tp_info.tp_data = stream.ConsumeIntegral<int>();
  rdata.tp_info.op_key.rdata = &rdata;
  rdata.msg_info.msg = NULL;
  rdata.msg_info.len = stream.ConsumeIntegral<int>();
  rdata.msg_info.msg_buf = (char*)stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size)).c_str();

  // Call the function to fuzz
  pjsip_transaction *p_tsx = NULL;
  int result = pjsip_tsx_create_uas(&tsx_user, &rdata, &p_tsx);

  // Clean up
  if (p_tsx) {
    pjsip_tsx_terminate(p_tsx, 200);
  }
  pjsip_endpt_destroy(endpt);
  pj_shutdown();

  return 0;
}