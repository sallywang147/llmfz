#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "../src/debug.h"
#include "../src/sdp.h"
#include "../src/utils.h"

extern "C" {
  #include <glib.h>
}

int janus_log_level = LOG_NONE;
gboolean janus_log_timestamps = FALSE;
gboolean janus_log_colors = FALSE;
char *janus_log_global_prefix = NULL;
int lock_debug = 0;

/* This is to avoid linking with openSSL */
int RAND_bytes(uint8_t *key, int len) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  /* Sanity Checks */
  if (size < 1)
    return 0;
  if (size > 1024)
    return 0;

  /* Create a FuzzedDataProvider object */
  FuzzedDataProvider stream(data, size);

  /* Extract the name and address */
  std::string name = stream.ConsumeRandomLengthString();
  std::string address = stream.ConsumeRandomLengthString();

  /* Call the function */
  struct janus_sdp *sdp = janus_sdp_generate_offer((char *)name.c_str(), (char *)address.c_str());

  /* Free the SDP */
  janus_sdp_free(sdp);

  return 0;
}