 #include <fuzzer/FuzzedDataProvider.h>

#include <hostapd.h>
#include <hostapd_iface.h>
#include <hostapd_logger.h>
#include <hostapd_module.h>
#include <hostapd_sta.h>
#include <ieee802_11_defs.h>
#include <ieee802_1x.h>
#include <wpa_supplicant/driver.h>
#include <wpa_supplicant/ieee802_11.h>
#include <wpa_supplicant/wpa.h>
#include <wpa_supplicant/wpa_common.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct hostapd_iface *iface = os_zalloc(sizeof(*iface));
  if (!iface)
    return 0;
  iface->conf = os_zalloc(sizeof(*iface->conf));
  if (!iface->conf) {
    os_free(iface);
    return 0;
  }
  iface->conf->driver = os_strdup("nl80211");
  iface->conf->ssid.ssid_len = stream.ConsumeIntegralInRange(0, 32);
  iface->conf->ssid.ssid =
      (u8*)os_malloc(iface->conf->ssid.ssid_len + 1);
  if (!iface->conf->ssid.ssid) {
    os_free(iface->conf->driver);
    os_free(iface);
    return 0;
  }
  stream.ConsumeBytes<u8>(iface->conf->ssid.ssid,
                          iface->conf->ssid.ssid_len);
  iface->conf->ssid.ssid[iface->conf->ssid.ssid_len] = '\0';
  iface->conf->channel = stream.ConsumeIntegralInRange(1, 14);
  iface->conf->ieee80211n = 1;
  iface->conf->ieee80211ac = 1;
  iface->conf->wpa = 2;
  iface->conf->wpa_key_mgmt = WPA_KEY_MGMT_PSK;
  iface->conf->wpa_pairwise = WPA_CIPHER_CCMP;
  iface->conf->wpa_group = WPA_CIPHER_CCMP;
  iface->conf->wpa_passphrase = os_strdup("12345678");
  iface->conf->eapol_key_index_workaround = 1;
  iface->conf->wep_key_len = 13;
  iface->conf->wep_key[0] = 0x01;
  iface->conf->wep_key[1] = 0x23;
  iface->conf->wep_key[2] = 0x45;
  iface->conf->wep_key[3] = 0x67;
  iface->conf->wep_key[4] = 0x89;
  iface->conf->wep_key[5] = 0xab;
  iface->conf->wep_key[6] = 0xcd;
  iface->conf->wep_key[7] = 0xef;
  iface->conf->wep_key[8] = 0x01;
  iface->conf->wep_key[9] = 0x23;
  iface->conf->wep_key[10] = 0x45;
  iface->conf->wep_key[11] = 0x67;
  iface->conf->wep_key[12] = 0x89;
  iface->conf->wep_key_len_2 = 13;
  iface->conf->wep_key_2[0] = 0x01;
  iface->conf->wep_key_2[1] = 0x23;
  iface->conf->wep_key_2[2] = 0x45;
  iface->conf->wep_key_2[3] = 0x67;
  iface->conf->wep_key_2[4] = 0x89;
  iface->conf->wep_key_2[5] = 0xab;
  iface->conf->wep_key_2[6] = 0xcd;
  iface->conf->wep_key_2[7] = 0xef;
  iface->conf->wep_key_2[8] = 0x01;
  iface->conf->wep_key_2[9] = 0x23;
  iface->conf->wep_key_2[10] = 0x45;
  iface->conf->wep_key_2[11] = 0x67;
  iface->conf->wep_key_2[12] = 0x89;
  iface->conf->wep_key_len_3 = 13;
  iface->conf->wep_key_3[0] = 0x01;
  iface->conf->wep_key_3[1] = 0x23;
  iface->conf->wep_key_3[2] = 0x45;
  iface->conf->wep_key_3[3] = 0x67;
  iface->conf->wep_key_3[4] = 0x89;
  iface->conf->wep_key_3[5] = 0xab;
  iface->conf->wep_key_3[6] = 0xcd;
  iface->conf->wep_key_3[7] = 0xef;
  iface->conf->wep_key_3[8] = 0x01;
  iface->conf->wep_key_3[9] = 0x23;
  iface->conf->wep_key_3[10] = 0x45;
  iface->conf->wep_key_3[11] = 0x67;
  iface->conf->wep_key_3[12] = 0x89;
  iface->conf->wep_key_len_4 = 13;
  iface->conf->wep_key_4[0] = 0x01;
  iface->conf->wep_key_4[1] = 0x23;
  iface->conf->wep_key_4[2] = 0x45;
  iface->conf->wep_key_4[3] = 0x67;
  iface->conf->wep_key_4[4] = 0x89;
  iface->conf->wep_key_4[5] = 0xab;
  iface->conf->wep_key_4[6] = 0xcd;
  iface->conf->wep_key_4[7] = 0xef;
  iface->conf->wep_key_4[8] = 0x01;
  iface->conf->wep_key_4[9] = 0x23;
  iface->conf->wep_key_4[10] = 0x45;
  iface->conf->wep_key_4[11] = 0x67;
  iface->conf->wep_key_4[12] = 0x89;
  iface->conf->auth_algs = WPA_AUTH_ALG_OPEN;
  iface->conf->wpa_group_rekey = 600;
  iface->conf->wpa_gmk_rekey = 86400;
  iface->conf->wpa_strict_rekey = 1;
  iface->conf->wpa_disable_eapol_key_retries = 1;
  iface->conf->eapol_version = 2;
  iface->conf->ocv = 1;
  iface->conf->ignore_broadcast_ssid = 1;
  iface->conf->wmm_enabled = 1;
  iface->conf->wmm_ac_bk_cwmin = 4;
  iface->conf->wmm_ac_bk_cwmax = 10;
  iface->conf->wmm_ac_bk_aifs = 7;
  iface->conf->wmm_ac_bk_txop_limit = 0;
  iface->conf->wmm_ac_be_cwmin = 4;
  iface->conf->wmm_ac_be_cwmax = 10;
  iface->conf->wmm_ac_be_aifs = 3;
  iface->conf->wmm_ac_be_txop_limit = 0;
  iface->conf->wmm_ac_vi_cwmin = 3;
  iface->conf->wmm_ac_vi_cwmax = 4;
  iface->conf->wmm_ac_vi_aifs = 1;
  iface->conf->wmm_ac_vi_txop_limit = 94;
  iface->conf->wmm_ac_vo_cwmin = 2;
  iface->conf->wmm_ac_vo_cwmax = 3;
  iface->conf->wmm_ac_vo_aifs = 1;
  iface->conf->wmm_ac_vo_txop_limit = 47;
  iface->conf->beacon_int = 100;
  iface->conf->dtim_period = 2;
  iface->conf->rts_threshold = 2347;
  iface->conf->fragm_threshold = 2346;
  iface->conf->max_listen_interval = 65535;
  iface->conf->send_probe_response = 1;
  iface->conf->hw_mode = HOSTAPD_MODE_IEEE80211G;
  iface->conf->ieee80211d = 1;
  iface->conf->ieee80211h = 1;
  iface->conf->ieee80211n = 1;
  iface->conf->ieee80211ac = 1;
  iface->conf->require_ie = 1;
  iface->conf->require_wpa = 2;
  iface->conf->ap_max_inactivity = 300;
  iface->conf->max_num_sta = 255;
  iface->conf->wep_default_key = 0;
  iface->conf->logger_stdout = 1;
  iface->conf->logger_syslog = 1;
  iface->conf->logger_syslog_level = 2;
  iface->conf->logger_file = os_strdup("/dev/null");
  iface->conf->logger_file_level = 2;
  iface->conf->ctrl_interface = os_strdup("none");
  iface->conf->ctrl_interface_group = 0;
  iface->conf->eapol_auth = os_strdup("HOSTAPD");
  iface->conf->eapol_ca_cert = os_strdup("hostapd.pem");
  iface->conf->eapol_server_cert = os_strdup("hostapd.pem");
  iface->conf->eapol_server_key = os_strdup("hostapd.key");
  iface->conf->ca_cert = os_strdup("ca.pem");
  iface->conf->server_cert = os_strdup("server.pem");
  iface->conf->private_key = os_strdup("private.key");
  iface->conf->private_key_passwd = os_strdup("12345678");
  iface->conf->dh_file = os_strdup("dh.pem");
  iface->conf->openssl_ciphers = os_strdup("ALL");
  iface->conf->eap_server = 1;
  iface->conf->eap_user_file = os_strdup("hostapd.eap_user");
  iface->conf->eap_sim_db = os_strdup("hostapd.eap_sim");
  iface->conf->pac_key_lifetime = 600;
  iface->conf->pac_key_refresh_time = 300;
  iface->conf->eap_fast_a_id = os_strdup("hostapd");
  iface->conf->eap_fast_a_id_info = os_strdup("hostapd");
  iface->conf->eap_fast_prov = os_strdup("/var/run/hostapd-");
  iface->conf->eap_fast_prov_reconnect = 1;
  iface->conf->pac_key_lifetime = 600;
  iface->conf->pac_key_refresh_time = 300;
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678");
  iface->conf->radius_server_auth_port = 1812;
  iface->conf->radius_server_acct_port = 1813;
  iface->conf->radius_server_shared_secret = os_strdup("12345678