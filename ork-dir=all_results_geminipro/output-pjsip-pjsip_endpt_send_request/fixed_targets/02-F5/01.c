#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pj/assert.h>
#include <pj/log.h>
#include <pj/pool.h>
#include <pj/string.h>
#include <pj/stun.h>
#include <pj/transport.h>
#include <pj/util.h>
#include <pjlib.h>
#include <pjmedia/sdp.h>
#include <pjmedia/transport_udp.h>
#include <pjsip/sip_message.h>
#include <pjsip/sip_ua.h>

#include <fuzzer/FuzzedDataProvider.h>

#define MAX_TOKEN_SIZE 1024

extern "C" {
#include <pjsip/sip_inv.h>
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  pj_pool_t *pool;
  pj_status_t status;
  pjsip_endpoint *endpt;
  pjsip_tx_data *tdata;
  char token[MAX_TOKEN_SIZE];
  func_type *cb;

  /* Initialize pjlib */
  status = pj_init();
  PJ_ASSERT_RETURN(status == PJ_SUCCESS, 1);

  /* Create a pool */
  pool = pj_pool_create();

  /* Create an endpoint */
  status = pjsip_endpt_create(pool, NULL, &endpt);
  PJ_ASSERT_RETURN(status == PJ_SUCCESS, 1);

  /* Create a transaction data */
  tdata = pjsip_tx_data_create(pool);

  /* Generate a random token */
  stream.ConsumeBytesAsString(MAX_TOKEN_SIZE - 1).copy(token, MAX_TOKEN_SIZE - 1);
  token[MAX_TOKEN_SIZE - 1] = '\0';

  /* Create a callback function */
  cb = NULL;

  /* Send the request */
  status = pjsip_inv_send_request(endpt, tdata, 0, token, cb);
  PJ_ASSERT_RETURN(status == PJ_SUCCESS, 1);

  /* Destroy the endpoint */
  pjsip_endpt_destroy(endpt);

  /* Destroy the pool */
  pj_pool_release(pool);

  /* Shutdown pjlib */
  pj_shutdown();

  return 0;
}