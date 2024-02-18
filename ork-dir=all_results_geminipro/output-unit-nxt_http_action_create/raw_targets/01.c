#include "Fuzz_http.h"

#define kMinInputLength 10
#define kMaxInputLength 5120
static int DoInit = 0;

nxt_lvlhsh_t hash;

extern char **environ;

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // src/test/nxt_http_parse_test.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  if (!DoInit) {
    nxt_lib_start("tests", NULL, &environ);
    nxt_memzero(&hash, sizeof(nxt_lvlhsh_t));

    nxt_http_fields_hash(&hash, nxt_h1p_fields, nxt_nitems(nxt_h1p_fields));
    DoInit = 1;
  }

  nxt_str_t nxt_http_request;

  nxt_http_request.length = Size;
  nxt_http_request.start = (uint8_t *)Data;

  return nxt_http_parse_fuzz(&nxt_http_request, &hash);
}

nxt_int_t nxt_http_parse_fuzz(nxt_str_t *request, nxt_lvlhsh_t *hash) {

  nxt_mp_t *mp;
  nxt_buf_mem_t buf;
  nxt_http_request_parse_t rp;

  buf.start = request->start;
  buf.end = request->start + request->length;

  nxt_memzero(&rp, sizeof(nxt_http_request_parse_t));

  mp = nxt_mp_create(1024, 128, 256, 32);

  nxt_http_parse_request_init(&rp, mp);

  buf.pos = buf.start;
  buf.free = buf.end;

  if (nxt_slow_path(nxt_http_parse_request(&rp, &buf) == NXT_DONE)) {
    nxt_http_fields_process(rp.fields, hash, NULL);
  }

  nxt_mp_destroy(mp);

  return NXT_OK;
}

struct nxt_http_action_s * nxt_http_action_create(struct nxt_task_s * task, struct nxt_router_temp_conf_t * tmcf, struct nxt_str_t * pass) {
  struct nxt_http_action_s * action;

  action = nxt_mp_alloc(task->mp, sizeof(struct nxt_http_action_s));
  if (action == NULL) {
    return NULL;
  }

  nxt_memzero(action, sizeof(struct nxt_http_action_s));

  action->task = task;
  action->tmcf = tmcf;
  action->pass = pass;

  action->status = NXT_HTTP_OK;
  action->headers_sent = 0;
  action->body_sent = 0;
  action->keepalive = 1;
  action->file_fd = NXT_INVALID_FILE;

  action->next = NULL;
  action->prev = NULL;

  return action;
}