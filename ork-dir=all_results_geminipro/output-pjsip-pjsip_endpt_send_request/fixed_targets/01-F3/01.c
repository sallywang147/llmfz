#include <pjsip-util.h>
#include <pjsip.h>
#include <pjsip/sip_message.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize pjsip_endpoint
  pjsip_endpoint *endpt = pjsip_endpoint_create(NULL, NULL);

  // Initialize pjsip_tx_data
  pjsip_tx_data *tdata = pjsip_tx_data_create();
  tdata->msg = pjsip_msg_create(NULL, NULL);

  // Initialize timeout
  int timeout = stream.ConsumeIntegralInRange(0, 1000);

  // Initialize token
  std::string token = stream.ConsumeRandomLengthString();
  char *token_ptr = token.c_str();

  // Initialize cb
  func_type *cb = NULL;

  // Call the function
  int result = pjsip_endpt_send_request(endpt, tdata, timeout, token_ptr, cb);

  // Destroy pjsip_endpoint
  pjsip_endpoint_destroy(endpt);

  // Destroy pjsip_tx_data
  pjsip_tx_data_destroy(tdata);

  return result;
}