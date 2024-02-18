#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "includes.h"
#include "common.h"
#include "wpa_supplicant_i.h"
#include "fuzzer-common.h"

static const struct wpa_driver_ops *const wpa_drivers[] = { NULL };

static int wpa_supplicant_init_iface_fuzz(struct wpa_supplicant *wpa_s,
                                        struct wpa_interface *iface)
{
	FuzzedDataProvider stream(data, size);
	char *ifname = stream.ConsumeRandomLengthString();
	char *confname = stream.ConsumeRandomLengthString();
	char *driver = stream.ConsumeRandomLengthString();
	char *ctrl_interface = stream.ConsumeRandomLengthString();
	char *bridge = stream.ConsumeRandomLengthString();
	char *scan_file = stream.ConsumeRandomLengthString();
	int debug_level = stream.ConsumeIntegral<int>();
	int wps_disabled = stream.ConsumeBool();
	int ap_scan = stream.ConsumeBool();
	int scan_interval = stream.ConsumeIntegral<int>();
	int fast_reauth = stream.ConsumeBool();
	int driver_param = stream.ConsumeIntegral<int>();
	int p2p_disabled = stream.ConsumeBool();
	int external_sim = stream.ConsumeBool();
	int disassoc_low_ack = stream.ConsumeBool();
	int ignore_broadcast_ssid = stream.ConsumeBool();
	int allow_p2p_group_formation = stream.ConsumeBool();
	int dual_band_rssi_threshold = stream.ConsumeIntegral<int>();
	int dual_band_select = stream.ConsumeIntegral<int>();
	int freq_list_num = stream.ConsumeIntegral<int>();
	struct wpa_freq_range freq_list[freq_list_num];
	int num_multichan_concurrent = stream.ConsumeIntegral<int>();
	struct wpa_multichan_concurrent multichan_concurrent[num_multichan_concurrent];
	int max_num_sta = stream.ConsumeIntegral<int>();
	int max_inactivity_sec = stream.ConsumeIntegral<int>();
	int max_auth_tries = stream.ConsumeIntegral<int>();
	int wpa_rsc_relaxation = stream.ConsumeBool();
	int set_sta_authorized = stream.ConsumeBool();
	int macaddr_acl = stream.ConsumeBool();
	int wps_nfc_dev_pw_id = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pubkey_id = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_privkey_id = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pubkey_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_privkey_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pubkey = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_privkey = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_hash = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_mac = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_prime = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_prime_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_ie_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_ie = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_addr = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_addr_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pw_id = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pw_id_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pw = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pw_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_pw = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_pw_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_addr = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_addr_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_pw = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_pw_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_freq = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_freq_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_ssid = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_ssid_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_hash = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_hash_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_s1 = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_s1_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_s2 = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_s2_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_deriv_nonce = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_deriv_nonce_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_auth_type_flags = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_auth_type_flags_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_encr_type_flags = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_encr_type_flags_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_conn_capab_flags = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_conn_capab_flags_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_config_methods = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_config_methods_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_rf_bands = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_rf_bands_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_type = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_type_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_manufacturer = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_manufacturer_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_model_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_model_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_model_number = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_model_number_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_serial_number = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_serial_number_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_primary_dev_type = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_primary_dev_type_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_device_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_device_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_config_error = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_config_error_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password_id = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password_id_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_manufacturer = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_manufacturer_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_model_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_model_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_model_number = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_model_number_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_serial_number = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_serial_number_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_primary_dev_type = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_primary_dev_type_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_device_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_device_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_config_error = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_config_error_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_password_id = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_password_id_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_password = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_password_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_req_to_enroll = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_req_to_enroll_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_resp_to_enroll = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_resp_to_enroll_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dev_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dev_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_manufacturer = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_manufacturer_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_model_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_model_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_model_number = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_model_number_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_serial_number = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_serial_number_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_primary_dev_type = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_primary_dev_type_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_device_name = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_device_name_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_config_error = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_config_error_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dev_password_id = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dev_password_id_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dev_password = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dev_password_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_uuid_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_uuid_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_uuid_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_uuid_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_uuid_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_uuid_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_uuid_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_uuid_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_uuid_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_uuid_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_uuid_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_uuid_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_dev_pw = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_dev_pw_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_assoc_dev_pw = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_assoc_dev_pw_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_new_dev_pw = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_new_dev_pw_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_client_cert = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_client_cert_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_server_cert = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_server_cert_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_root_cert = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_root_cert_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_private_key = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_private_key_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_public_key = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_public_key_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_public_key = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_public_key_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_public_key = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_public_key_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_pubkey_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_pubkey_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_pubkey_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_pubkey_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_pubkey_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_pubkey_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_pubkey_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_pubkey_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_pubkey_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_pubkey_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_pubkey_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_pubkey_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_privkey_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_privkey_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_privkey_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_privkey_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_privkey_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_privkey_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_privkey_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_privkey_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_privkey_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_privkey_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_privkey_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_privkey_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_hash_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_hash_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_hash_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_hash_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_hash_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_hash_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_hash_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_hash_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_hash_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_hash_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_hash_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_hash_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_mac_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_mac_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_mac_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dh_mac_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_mac_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_mac_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_mac_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dh_mac_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_mac_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_mac_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_mac_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_dh_mac_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_prime_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_prime_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_prime_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_r_prime_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_r_prime_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_r_prime_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_r_prime_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_r_prime_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_r_prime_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_r_prime_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_r_prime_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_r_prime_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_attrs = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_attrs_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_attrs = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_attrs_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_attrs = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_attrs_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_deriv_nonce_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_deriv_nonce_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_deriv_nonce_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_deriv_nonce_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_key_deriv_nonce_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_key_deriv_nonce_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_key_deriv_nonce_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_key_deriv_nonce_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_key_deriv_nonce_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_key_deriv_nonce_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_key_deriv_nonce_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_key_deriv_nonce_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pkhash_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pkhash_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pkhash_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_pkhash_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_pkhash_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_pkhash_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_pkhash_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_pkhash_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_pkhash_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_pkhash_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_pkhash_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_pkhash_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_akm = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_akm_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_akm = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_akm_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_akm = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_akm_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_cipher_suite = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_cipher_suite_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_cipher_suite = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_cipher_suite_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_cipher_suite = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_cipher_suite_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_group_hint = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_group_hint_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_group_hint = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_group_hint_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_group_hint = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_group_hint_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_wrap_auth = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_key_wrap_auth_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_key_wrap_auth = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_key_wrap_auth_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_key_wrap_auth = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_key_wrap_auth_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_mac_addr = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_mac_addr_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_mac_addr = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_mac_addr_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_mac_addr = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_mac_addr_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_dev_pw_id_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_dev_pw_id_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_dev_pw_id_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_dev_pw_id_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_dev_pw_id_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_dev_pw_id_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_dev_pw_id_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_dev_pw_id_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_dev_pw_id_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_dev_pw_id_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_dev_pw_id_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_dev_pw_id_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_assoc_dev_pw_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_assoc_dev_pw_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_assoc_dev_pw_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_assoc_dev_pw_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_assoc_dev_pw_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_assoc_dev_pw_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_assoc_dev_pw_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_assoc_dev_pw_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_assoc_dev_pw_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_assoc_dev_pw_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_assoc_dev_pw_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_assoc_dev_pw_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_new_dev_pw_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_new_dev_pw_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_new_dev_pw_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_oob_new_dev_pw_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_new_dev_pw_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_new_dev_pw_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_new_dev_pw_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_oob_new_dev_pw_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_new_dev_pw_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_new_dev_pw_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_new_dev_pw_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_new_oob_new_dev_pw_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password_id_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password_id_e_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password_id_r = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_dev_password_id_r_len = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_password_id_e = stream.ConsumeIntegral<int>();
	int wps_nfc_dh_assoc_dev_password_id