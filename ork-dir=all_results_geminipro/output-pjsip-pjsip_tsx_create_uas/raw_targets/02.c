#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pjlib-util.h>
#include <pjlib.h>
#include <pjsip.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  if (Size < 1) {
    return 1;
  }

  pj_pool_t *pool;
  pj_status_t status;

  pj_pool_factory *factory = pj_pool_factory_default();
  pool = pj_pool_create(factory, NULL, 4096, 4096, NULL);

  struct pjsip_module *tsx_user = pjsip_tsx_user_instance();
  struct pjsip_rx_data *rdata = (struct pjsip_rx_data *)malloc(sizeof(struct pjsip_rx_data));
  struct pjsip_transaction *p_tsx;

  pj_str_t str;
  str.ptr = (char *)Data;
  str.slen = Size;

  rdata->msg_info.method = &str;
  rdata->msg_info.uri = &str;
  rdata->msg_info.to = &str;
  rdata->msg_info.from = &str;
  rdata->msg_info.body = &str;

  status = pjsip_tsx_create_uas(tsx_user, rdata, &p_tsx);
  if (status != PJ_SUCCESS) {
    abort();
  }

  pj_pool_release(pool);
  free(rdata);
  return 0;
}