#include <algorithm>  // For std::min

#include <fuzzer/FuzzedDataProvider.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hostapd.h"
#include "hostapd_cfg.h"
#include "hostapd_log.h"
#include "hostapd_main.h"

extern "C" {
#include <algorithm>
#include "hostapd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct hostapd_iface *iface =
      (struct hostapd_iface *)malloc(sizeof(struct hostapd_iface));
  if (iface == NULL) {
    return 0;
  }

  iface->config_fname = (char *)malloc(std::min(size, (size_t)255));  // Limit the size of the config file name to prevent excessive memory allocation
  if (iface->config_fname == NULL) {
    free(iface);
    return 0;
  }
  stream.ConsumeBytes<char>(iface->config_fname, std::min(size, (size_t)255));

  hostapd_reload_config(iface);

  free(iface->config_fname);
  free(iface);

  return 0;
}