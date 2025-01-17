#include "includes.h"

#include "common.h"
#include "eloop.h"
#include "wpa_supplicant_i.h"
#include "fuzzer-common.h"

extern "C" {
#include "fuzzer-common.c"
}

static int fuzz_wpa_supplicant_init_iface(struct wpa_supplicant *wpa_s,
					   struct wpa_interface *iface)
{
	return wpa_supplicant_init_iface(wpa_s, iface);
}


int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	struct wpa_supplicant wpa_s;
	struct wpa_interface iface;

	wpa_fuzzer_set_debug_level();

	if (os_program_init())
		return -1;

	os_memset(&wpa_s, 0, sizeof(wpa_s));
	os_memset(&iface, 0, sizeof(iface));

	if (eloop_init()) {
		wpa_printf(MSG_ERROR, "Failed to initialize event loop");
		goto fail;
	}

	fuzz_wpa_supplicant_init_iface(&wpa_s, &iface);

	wpa_printf(MSG_DEBUG, "Starting eloop");
	eloop_run();
	wpa_printf(MSG_DEBUG, "eloop done");

fail:
	eloop_destroy();

	os_program_deinit();

	return 0;
}