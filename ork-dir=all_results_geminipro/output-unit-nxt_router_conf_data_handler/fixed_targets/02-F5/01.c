#include "Fuzz_http.h"

#define kMinInputLength 10
#define kMaxInputLength 5120

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { // src/test/nxt_http_parse_test.c

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
}

void nxt_router_conf_data_handler(struct nxt_task_s *task, struct nxt_port_recv_msg_s *msg) {
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

nxt_http_parser_t *nxt_http_parser_create(nxt_mp_t *mp, nxt_buf_t *buf) {
  nxt_http_parser_t *parser;

  parser = nxt_mp_alloc(mp, sizeof(nxt_http_parser_t));
  if (parser == NULL) {
    return NULL;
  }

  nxt_memzero(parser, sizeof(nxt_http_parser_t));

  parser->mp = mp;
  parser->buf = buf;

  return parser;
}

void nxt_http_parser_init(nxt_http_parser_t *parser, nxt_buf_t *buf) {
  parser->buf = buf;
  parser->pos = buf->start;
  parser->last = buf->pos;
  parser->end = buf->end;
}

nxt_int_t nxt_http_parser_parse_line(nxt_http_parser_t *parser, nxt_str_t **line) {
  u_char ch;
  nxt_str_t *s;

  s = *line = nxt_mp_alloc(parser->mp, sizeof(nxt_str_t));
  if (s == NULL) {
    return NXT_ERROR;
  }

  nxt_memzero(s, sizeof(nxt_str_t));

  while (parser->pos < parser->end) {

    ch = *parser->pos++;

    if (ch == LF) {
      parser->last = parser->pos;
      s->end = parser->last - 1;

      if (s->end >= s->start && *(s->end) == CR) {
        s->end--;
      }

      return NXT_OK;
    }

    if (ch == CR) {
      continue;
    }

    if (s->start == NULL) {
      s->start = parser->pos - 1;
    }
  }

  parser->last = parser->pos;
  s->end = parser->last;

  return NXT_AGAIN;
}

nxt_str_t *nxt_http_parser_get_key(nxt_str_t *line) {
  nxt_str_t *key;

  key = nxt_mp_alloc(line->mp, sizeof(nxt_str_t));
  if (key == NULL) {
    return NULL;
  }

  nxt_memzero(key, sizeof(nxt_str_t));

  key->start = line->start;

  while (key->start < line->end && *key->start != ':') {
    key->start++;
  }

  if (key->start == line->end) {
    return NULL;
  }

  key->end = key->start;

  while (key->end < line->end && *key->end != ' ') {
    key->end++;
  }

  if (key->end == line->end) {
    return NULL;
  }

  nxt_str_trim(key);

  return key;
}

nxt_str_t *nxt_http_parser_get_value(nxt_str_t *line) {
  nxt_str_t *value;

  value = nxt_mp_alloc(line->mp, sizeof(nxt_str_t));
  if (value == NULL) {
    return NULL;
  }

  nxt_memzero(value, sizeof(nxt_str_t));

  value->start = line->end;

  while (value->start < line->end && *value->start == ' ') {
    value->start++;
  }

  if (value->start == line->end) {
    return NULL;
  }

  value->end = line->end;

  nxt_str_trim(value);

  return value;
}

void nxt_http_parser_set_var(nxt_http_vars_t *vars, nxt_str_t *key, nxt_str_t *value) {
  nxt_http_var_t *var;

  var = nxt_mp_alloc(vars->mp, sizeof(nxt_http_var_t));
  if (var == NULL) {
    return;
  }

  nxt_memzero(var, sizeof(nxt_http_var_t));

  var->key = key;
  var->value = value;

  nxt_list_add(&vars->vars, &var->list);
}