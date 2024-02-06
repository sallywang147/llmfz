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
extern "C" {
int RAND_bytes(uint8_t *key, int len) { return 0; }
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  /* Sanity Checks */
  if (size < 1)
    return 0;
  char *sdp = g_strndup((char *)data, size);
  if (!sdp)
    return 0;
  /* Parse SDP */
  struct janus_sdp *offer = janus_sdp_parse(sdp, size);
  g_free(sdp);
  if (!offer)
    return 0;
  /* Create answer */
  struct janus_sdp *answer = janus_sdp_create();
  if (!answer) {
    janus_sdp_destroy(offer);
    return 0;
  }
  /* Generate answer */
  janus_sdp_generate_answer(offer, answer);
  /* Generate answer for each m-line */
  GList *temp = offer->m_lines;
  while (temp) {
    struct janus_sdp_mline *offered = (struct janus_sdp_mline *)temp->data;
    janus_sdp_generate_answer_mline(offer, answer, offered);
    temp = temp->next;
  }
  /* Free resources */
  janus_sdp_destroy(offer);
  janus_sdp_destroy(answer);

  return 0;
}