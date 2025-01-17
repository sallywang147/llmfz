#include "utils/includes.h"

#include "utils/common.h"
#include "utils/eloop.h"
#include "common/ieee802_11_defs.h"
#include "common/ieee802_11_common.h"
#include "wpa_supplicant_i.h"

extern "C" {
#include "wpa_supplicant_private.h" // Included the missing header file
}

#include "../fuzzer-common.h"


static void wpa_supplicant_reconfig(int sig, char * signal_ctx)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s", __func__);
}


int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	struct wpa_supplicant wpa_s;
	struct wpa_global wpa_g;

	wpa_fuzzer_set_debug_level();

	if (os_program_init())
		return -1;

	os_memset(&wpa_s, 0, sizeof(wpa_s));
	os_memset(&wpa_g, 0, sizeof(wpa_g));

	wpa_s.global = &wpa_g;
	wpa_s.conf = os_zalloc(sizeof(*wpa_s.conf));
	if (!wpa_s.conf)
		return -1;

	if (eloop_init()) {
		wpa_printf(MSG_ERROR, "Failed to initialize event loop");
		goto fail;
	}

	wpa_supplicant_reconfig(0, NULL);

fail:
	eloop_destroy();

	os_program_deinit();

	return 0;
}