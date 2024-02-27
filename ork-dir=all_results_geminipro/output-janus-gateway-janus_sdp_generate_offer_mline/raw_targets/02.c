#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "../src/debug.h"
#include "../src/sdp.h"
#include "../src/utils.h"
#include <glib.h>

int janus_log_level = LOG_NONE;
gboolean janus_log_timestamps = FALSE;
gboolean janus_log_colors = FALSE;
char *janus_log_global_prefix = NULL;
int lock_debug = 0;

/* This is to avoid linking with openSSL */
int RAND_bytes(uint8_t *key, int len) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  /* Sanity Checks */
  /* Max UDP payload with MTU=1500 */
  if (size > 1472)
    return 0;
  /* libnice checks that a packet length is positive */
  if (size <= 0)
    return 0;
  /* Janus checks for a minimum packet length
   * and the RTP header type value */
  if (!janus_is_rtp((char *)data, size))
    return 0;

  char sdes_item[16];
  janus_rtp_header_extension_parse_rid((char *)data, size, 1, sdes_item, sizeof(sdes_item));
  janus_rtp_header_extension_parse_mid((char *)data, size, 1, sdes_item, sizeof(sdes_item));

  /* Do same checks that libsrtp does */
  if (srtp_validate_rtp_header((char *)data, size) < 0)
    return 0;

  /* RTP extensions parsers */
  guint16 transport_seq_num;
  gboolean c, f, r1, r0;
  uint8_t dd[256];
  int sizedd = sizeof(dd);
  janus_rtp_header_extension_parse_audio_level((char *)data, size, 1, NULL, NULL);
  janus_rtp_header_extension_parse_playout_delay((char *)data, size, 1, NULL, NULL);
  janus_rtp_header_extension_parse_transport_wide_cc((char *)data, size, 1, &transport_seq_num);
  janus_rtp_header_extension_parse_abs_send_time((char *)data, size, 1, NULL);
  janus_rtp_header_extension_parse_abs_capture_time((char *)data, size, 1, NULL);
  janus_rtp_header_extension_parse_video_orientation((char *)data, size, 1, &c, &f, &r1, &r0);
  janus_rtp_header_extension_parse_dependency_desc((char *)data, size, 1, (uint8_t *)&dd, &sizedd);

  /* Extract codec payload */
  int plen = 0;
  char *payload = janus_rtp_payload((char *)data, size, &plen);
  if (!payload)
    return 0;
  /* Make a copy of payload */
  char copy_payload[plen];
  memcpy(copy_payload, payload, plen);

  /* H.264 targets */
  janus_h264_is_keyframe(payload, plen);

  /* VP8 targets */
  gboolean m = FALSE;
  uint16_t picid = 0;
  uint8_t tlzi = 0, tid = 0, ybit = 0, keyidx = 0;
  janus_vp8_simulcast_context vp8_context;
  memset(&vp8_context, 0, sizeof(janus_vp8_simulcast_context));
  janus_vp8_is_keyframe(payload, plen);
  janus_vp8_parse_descriptor(payload, plen, &m, &picid, &tlzi, &tid, &ybit, &keyidx);
  janus_vp8_simulcast_descriptor_update(copy_payload, plen, &vp8_context, TRUE);

  /* VP9 targets */
  int found = 0;
  janus_vp9_svc_info info;
  janus_vp9_is_keyframe(payload, plen);
  janus_vp9_parse_svc(payload, plen, &found, &info);

  /* Free resources */

  return 0;
}