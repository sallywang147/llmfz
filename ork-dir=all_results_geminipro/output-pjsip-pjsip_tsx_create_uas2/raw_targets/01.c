#include <pjsip.h>
#include <pjlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  pjsip_module tsx_user;
  pjsip_rx_data rdata;
  pj_grp_lock_t grp_lock;
  pjsip_transaction *p_tsx;

  pjsip_tsx_create_uas2(&tsx_user, &rdata, &grp_lock, &p_tsx);
  return 0;
}