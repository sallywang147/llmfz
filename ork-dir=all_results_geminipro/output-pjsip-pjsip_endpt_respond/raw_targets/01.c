#include <pjsip.h>
#include <pjlib.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  pjsip_endpoint *endpt = pjsip_endpt_create(NULL, NULL);
  pjsip_module *tsx_user = NULL;
  pjsip_rx_data *rdata = NULL;
  int st_code = 200;
  pj_str_t *st_text = NULL;
  pjsip_hdr *hdr_list = NULL;
  pjsip_msg_body *body = NULL;
  pjsip_transaction **p_tsx = NULL;

  pjsip_endpt_respond(endpt, tsx_user, rdata, st_code, st_text, hdr_list, body,
                      p_tsx);

  pjsip_endpt_destroy(endpt);
  return 0;
}