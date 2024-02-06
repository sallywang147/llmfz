#include "Fuzz_http.h"

#define kMinInputLength 10
#define kMaxInputLength 5120

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // src/test/nxt_http_parse_test.c

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  nxt_mp_t *mp;
  nxt_task_s task;
  nxt_port_recv_msg_s msg;

  mp = nxt_mp_create(1024, 128, 256, 32);

  nxt_memzero(&task, sizeof(nxt_task_s));
  nxt_memzero(&msg, sizeof(nxt_port_recv_msg_s));

  task.mp = mp;
  task.owner = NULL;

  msg.len = Size;
  msg.data = (uint8_t *)Data;

  nxt_router_conf_data_handler(&task, &msg);

  nxt_mp_destroy(mp);

  return 0;
}

void nxt_router_conf_data_handler(struct nxt_task_s * task, struct nxt_port_recv_msg_s * msg) {
  nxt_router_conf_data_t *conf;
  nxt_str_t *data;
  nxt_buf_t *buf;

  conf = nxt_mp_alloc(task->mp, sizeof(nxt_router_conf_data_t));
  if (conf == NULL) {
    return;
  }

  nxt_memzero(conf, sizeof(nxt_router_conf_data_t));

  conf->port = task->port;
  conf->task = task;
  conf->data = nxt_mp_alloc(task->mp, sizeof(nxt_str_t));
  if (conf->data == NULL) {
    return;
  }

  data = conf->data;

  data->start = msg->data;
  data->end = msg->data + msg->len;

  buf = nxt_buf_alloc(task->mp, nxt_buf_mem, data->start, data->end - data->start);
  if (buf == NULL) {
    return;
  }

  nxt_router_conf_data_parse(conf, buf);

  nxt_buf_free(buf);
}

nxt_int_t nxt_router_conf_data_parse(nxt_router_conf_data_t *conf, nxt_buf_t *buf) {
  nxt_str_t *line;
  nxt_str_t *value;
  nxt_str_t *key;

  nxt_http_parser_t parser;

  nxt_http_parser_init(&parser, buf);

  while (nxt_http_parser_parse_line(&parser, &line) == NXT_OK) {

    if (line->length == 0) {
      break;
    }

    key = nxt_http_parser_get_key(line);
    value = nxt_http_parser_get_value(line);

    if (nxt_slow_path(key == NULL || value == NULL)) {
      return NXT_ERROR;
    }

    nxt_http_parser_set_var(conf->vars, key, value);
  }

  return NXT_OK;
}