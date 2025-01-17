#include <janet.h>
#include <stdint.h>

extern "C" {
#include <janet_config.h>
#include <janet_core.h>
}

extern "C" size_t cfun_ev_thread(int, union Janet *);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  JanetParser parser;
  janet_parser_init(&parser);
  for (int i = 0, done = 0; i < size; i++) {
    switch (janet_parser_status(&parser)) {
    case JANET_PARSE_DEAD:
    case JANET_PARSE_ERROR:
      done = 1;
      break;
    case JANET_PARSE_PENDING:
      if (i == size) {
        janet_parser_eof(&parser);
      } else {
        janet_parser_consume(&parser, data[i]);
      }
      break;
    case JANET_PARSE_ROOT:
      if (i >= size) {
        janet_parser_eof(&parser);
      } else {
        janet_parser_consume(&parser, data[i]);
      }
      break;
    }

    if (done == 1)
      break;
  }
  janet_parser_deinit(&parser);

  /* get the root */
  Janet root = janet_parser_root(&parser);

  /* call cfun_ev_thread */
  cfun_ev_thread(0, &root);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}