 #include "utils/includes.h"

#include "utils/common.h"
#include "utils/eloop.h"
#include "utils/list.h"
#include "rsn_supp/wpa.h"
#include "rsn_supp/wpa_supplicant.h"
#include "../fuzzer-common.h"


static void * wpa_supplicant_get_network_ctx(void *ctx)
{
	return (void *) 1;
}


static void wpa_supplicant_deauthenticate(void *ctx, u16 reason_code)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s(%d)", __func__, reason_code);
}


static int wpa_supplicant_set_key(void *ctx, int link_id, enum wpa_alg alg,
				  const u8 *addr, int key_idx, int set_tx,
				  const u8 *seq, size_t seq_len,
				  const u8 *key, size_t key_len)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s(alg=%d addr=" MACSTR " key_idx=%d "
		   "set_tx=%d)",
		   __func__, alg, MAC2STR(addr), key_idx, set_tx);
	wpa_hexdump(MSG_DEBUG, "SUPP: set_key - seq", seq, seq_len);
	wpa_hexdump(MSG_DEBUG, "SUPP: set_key - key", key, key_len);
	return 0;
}


static int wpa_supplicant_mlme_setprotection(void *ctx, const u8 *addr,
					     int protection_type, int key_type)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s(addr=" MACSTR " protection_type=%d "
		   "key_type=%d)",
		   __func__, MAC2STR(addr), protection_type, key_type);
	return 0;
}


static void wpa_supplicant_cancel_auth_timeout(void *ctx)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s", __func__);
}


static void wpa_supplicant_rx_eapol(void *eloop_data, void *user_ctx)
{
	wpa_printf(MSG_DEBUG, "SUPP: RX EAPOL frame");
}


static int wpa_supplicant_ether_send(void *ctx, const u8 *dest, u16 proto,
				     const u8 *buf, size_t len)
{
	eloop_register_timeout(0, 0, wpa_supplicant_rx_eapol, ctx, NULL);
	return 0;
}


static u8 * wpa_supplicant_alloc_eapol(void *ctx, u8 type, const void *data,
					u16 data_len, size_t *msg_len, void **data_pos)
{
	struct ieee802_1x_hdr *hdr;

	wpa_printf(MSG_DEBUG, "SUPP: %s(type=%d data_len=%d)",
		   __func__, type, data_len);

	*msg_len = sizeof(*hdr) + data_len;
	hdr = os_malloc(*msg_len);
	if (hdr == NULL)
		return NULL;

	hdr->version = 2;
	hdr->type = type;
	hdr->length = host_to_be16(data_len);

	if (data)
		os_memcpy(hdr + 1, data, data_len);
	else
		os_memset(hdr + 1, 0, data_len);

	if (data_pos)
		*data_pos = hdr + 1;

	return (u8 *) hdr;
}


static int wpa_supplicant_get_beacon_ie(void *ctx)
{
	static const u8 wpaie[] = {
		0xdd, 0x16, 0x00, 0x50, 0xf2, 0x01, 0x01, 0x00,
		0x00, 0x50, 0xf2, 0x02, 0x01, 0x00, 0x00, 0x50,
		0xf2, 0x02, 0x01, 0x00, 0x00, 0x50, 0xf2, 0x02
	};
	static const u8 rsne[] = {
		0x30, 0x14, 0x01, 0x00, 0x00, 0x0f, 0xac, 0x04,
		0x01, 0x00, 0x00, 0x0f, 0xac, 0x04, 0x01, 0x00,
		0x00, 0x0f, 0xac, 0x02, 0xc0, 0x00
	};

	wpa_printf(MSG_DEBUG, "SUPP: %s", __func__);

	if (rsne[0] == WLAN_EID_RSN)
		return wpa_sm_set_ap_rsn_ie(ctx, rsne, 2 + rsne[1]);
	return wpa_sm_set_ap_wpa_ie(ctx, wpaie, 2 + wpaie[1]);
}


static int wpa_supplicant_set_wpa_ie(void *ctx, const u8 *wpa_ie, size_t wpa_ie_len)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s(wpa_ie_len=%lu)",
		   __func__, (unsigned long) wpa_ie_len);
	wpa_hexdump(MSG_DEBUG, "SUPP: wpa_ie", wpa_ie, wpa_ie_len);
	return 0;
}


static int wpa_supplicant_set_bssid(void *ctx, const u8 *bssid)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s", __func__);
	return 0;
}


static void wpa_supplicant_set_state(void *ctx, enum wpa_states state)
{
	wpa_printf(MSG_DEBUG, "SUPP: %s(state=%d)", __func__, state);
}


static int wpa_supplicant_init(struct wpa_supplicant *wpa_s)
{
	struct wpa_sm_ctx *ctx = os_zalloc(sizeof(*ctx));

	if (!ctx)
		return -1;

	ctx->ctx = wpa_s;
	ctx->msg_ctx = wpa_s;
	ctx->set_state = wpa_supplicant_set_state;
	ctx->get_network_ctx = wpa_supplicant_get_network_ctx;
	ctx->deauthenticate = wpa_supplicant_deauthenticate;
	ctx->ether_send = wpa_supplicant_ether_send;
	ctx->alloc_eapol = wpa_supplicant_alloc_eapol;
	ctx->set_key = wpa_supplicant_set_key;
	ctx->mlme_setprotection = wpa_supplicant_mlme_setprotection;
	ctx->cancel_auth_timeout = wpa_supplicant_cancel_auth_timeout;
	ctx->get_beacon_ie = wpa_supplicant_get_beacon_ie;
	ctx->set_wpa_ie = wpa_supplicant_set_wpa_ie;
	ctx->set_bssid = wpa_supplicant_set_bssid;
	wpa_s->wpa = wpa_sm_init(ctx);
	if (!wpa_s->wpa) {
		wpa_printf(MSG_DEBUG, "SUPP: wpa_sm_init() failed");
		return -1;
	}

	wpa_sm_set_own_addr(wpa_s->wpa, wpa_s->own_addr);
	wpa_sm_set_param(wpa_s->wpa, WPA_PARAM_PROTO, WPA_PROTO_RSN);
	wpa_sm_set_param(wpa_s->wpa, WPA_PARAM_PAIRWISE, WPA_CIPHER_CCMP);
	wpa_sm_set_param(wpa_s->wpa, WPA_PARAM_GROUP, WPA_CIPHER_CCMP);
	wpa_sm_set_param(wpa_s->wpa, WPA_PARAM_KEY_MGMT, WPA_KEY_MGMT_PSK);
	wpa_sm_set_param(wpa_s->wpa, WPA_PARAM_MFP, MGMT_FRAME_PROTECTION_OPTIONAL);
	wpa_sm_set_pmk(wpa_s->wpa, wpa_s->psk, PMK_LEN, NULL, NULL);

	return 0;
}


static void deinit(struct wpa_supplicant *wpa_s)
{
	wpa_sm_deinit(wpa_s->wpa);
}


int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	struct wpa_supplicant wpa_s;
	struct wpa_interface iface;

	wpa_fuzzer_set_debug_level();

	if (os_program_init())
		return -1;

	os_memset(&wpa_s, 0, sizeof(wpa_s));
	wpa_s.own_addr = (u8 *) "1234567890";
	os_memcpy(wpa_s.psk, "1234567890", PMK_LEN);
	wpa_s.parent = NULL;
	os_memset(&iface, 0, sizeof(iface));
	iface.ifname = "test";
	iface.driver = wpa_drivers[0];

	if (eloop_init()) {
		wpa_printf(MSG_ERROR, "Failed to initialize event loop");
		goto fail;
	}

	if (wpa_supplicant_init(&wpa_s) < 0)
		goto fail;

	wpa_supplicant_add_iface(&wpa_s.global, &iface, &wpa_s);

	wpa_printf(MSG_DEBUG, "Starting eloop");
	eloop_run();
	wpa_printf(MSG_DEBUG, "eloop done");

fail:
	deinit(&wpa_s);

	eloop_destroy();

	os_program_deinit();

	return 0;
}