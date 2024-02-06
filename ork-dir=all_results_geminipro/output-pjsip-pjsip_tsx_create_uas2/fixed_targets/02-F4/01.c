#include <pjsip.h>
#include <pjlib.h>

extern "C" {
#include <pjsip_ua.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct pjsip_module tsx_user;
  struct pjsip_rx_data rdata;
  struct pj_grp_lock_t grp_lock;
  struct pjsip_transaction *p_tsx;
  pjsip_tsx_create_uas2(&tsx_user, &rdata, &grp_lock, &p_tsx);
  pjsip_tsx_free(p_tsx);  // Declare pjsip_tsx_free
  return 0;
}