#include <fuzzer/FuzzedDataProvider.h>

#include <assert.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils/includes.h"

#include "common.h"
#include "utils/list.h"
#include "utils/eloop.h"
#include "common/ieee802_11_defs.h"
#include "common/wpa_ctrl.h"
#include "ap/hostapd.h"
#include "ap/ap_config.h"
#include "ap/ap_drv_ops.h"
#include "ap/ieee802_11.h"
#include "ap/sta_info.h"
#include "ap/wpa_auth.h"
#include "ap/wpa_auth_glue.h"
#include "ap/wpa_auth_i.h"
#include "ap/wpa_auth_sm.h"

extern "C" int wpa_supplicant_run(struct wpa_global * global);
extern "C" {
#include "ap/wpa_auth_if.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  struct wpa_global *global = wpa_global_init();
  wpa_supplicant_run(global);
  wpa_global_deinit(global);
  return 0;
}