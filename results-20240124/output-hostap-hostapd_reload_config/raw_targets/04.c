 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "hostapd.h"
#include "hostapd_iface.h"
#include "hostapd_config.h"
#include "hostapd_logger.h"
#include "hostapd_hw_drivers.h"
#include "hostapd_debug.h"
#include "hostapd_ctrl.h"
#include "hostapd_sta_info.h"
#include "hostapd_wpa_auth.h"
#include "hostapd_wpas_glue.h"
#include "utils/includes.h"
#include "utils/common.h"
#include "utils/eloop.h"
#include "utils/list.h"
#include "utils/os.h"
#include "utils/uuid.h"
#include "common/ieee802_11_defs.h"
#include "common/ieee802_11_common.h"
#include "common/wpa_ctrl.h"
#include "common/wpa_common.h"
#include "common/wpa_supplicant_i.h"
#include "common/ieee802_11_defs.h"
#include "common/ieee802_11_common.h"
#include "common/wpa_ctrl.h"
#include "common/wpa_common.h"
#include "common/wpa_supplicant_i.h"
#include "common/ieee802_11_defs.h"
#include "common/ieee802_11_common.h"
#include "common/wpa_ctrl.h"
#include "common/wpa_common.h"
#include "common/wpa_supplicant_i.h"

static struct hostapd_iface *
hostapd_fuzzer_iface_create(void)
{
	struct hostapd_iface *iface;
	struct hostapd_data *hapd;
	struct hostapd_config *conf;

	iface = os_zalloc(sizeof(*iface));
	if (!iface)
		return NULL;

	hapd = os_zalloc(sizeof(*hapd));
	if (!hapd) {
		os_free(iface);
		return NULL;
	}

	iface->hapd = hapd;

	conf = os_zalloc(sizeof(*conf));
	if (!conf) {
		os_free(iface);
		os_free(hapd);
		return NULL;
	}

	iface->conf = conf;

	return iface;
}

static void
hostapd_fuzzer_iface_destroy(struct hostapd_iface *iface)
{
	struct hostapd_data *hapd = iface->hapd;
	struct hostapd_config *conf = iface->conf;

	os_free(conf);
	os_free(hapd);
	os_free(iface);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	struct hostapd_iface *iface;

	iface = hostapd_fuzzer_iface_create();
	if (!iface)
		return 0;

	FuzzedDataProvider stream(data, size);

	std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
	iface->conf->ssid.ssid = bytes.data();
	iface->conf->ssid.ssid_len = bytes.size();

	bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
	iface->conf->wpa_psk = bytes.data();
	iface->conf->wpa_psk_len = bytes.size();

	hostapd_reload_config(iface);

	hostapd_fuzzer_iface_destroy(iface);

	return 0;
}