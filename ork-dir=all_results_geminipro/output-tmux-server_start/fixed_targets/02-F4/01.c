#include <assert.h>
#include <fcntl.h>
#include <stddef.h>

#include "tmux.h"

#define FUZZER_MAXLEN 512

struct event_base *libevent;

extern "C" {
#include "server.c"
}

int LLVMFuzzerTestOneInput(const u_char *data, size_t size) {
  struct bufferevent *vpty[2];
  struct window *w;
  struct window_pane *wp;
  int error;

  /*
   * Since AFL doesn't support -max_len paramenter we have to
   * discard long inputs manually.
   */
  if (size > FUZZER_MAXLEN)
    return 0;

  w = window_create(PANE_WIDTH, PANE_HEIGHT, 0, 0);
  wp = window_add_pane(w, NULL, 0, 0);
  bufferevent_pair_new(libevent, BEV_OPT_CLOSE_ON_FREE, vpty);
  wp->ictx = input_init(wp, vpty[0], NULL);
  window_add_ref(w, __func__);

  wp->fd = open("/dev/null", O_WRONLY);
  if (wp->fd == -1)
    errx(1, "open(\"/dev/null\") failed");
  wp->event = bufferevent_new(wp->fd, NULL, NULL, NULL, NULL);

  input_parse_buffer(wp, (u_char *)data, size);
  while (cmdq_next(NULL) != 0)
    ;
  error = event_base_loop(libevent, EVLOOP_NONBLOCK);
  if (error == -1)
    errx(1, "event_base_loop failed");

  assert(w->references == 1);
  window_remove_ref(w, __func__);

  bufferevent_free(vpty[0]);
  bufferevent_free(vpty[1]);

  return 0;
}

int LLVMFuzzerInitialize(__unused int *argc, __unused char ***argv) {
  const struct options_table_entry *oe;
  struct tmuxproc client;

  global_environ = environ_create();
  global_options = options_create(NULL);
  global_s_options = options_create(NULL);
  global_w_options = options_create(NULL);
  for (oe = options_table; oe->name != NULL; oe++) {
    if (oe->scope & OPTIONS_TABLE_SERVER)
      options_default(global_options, oe);
    if (oe->scope & OPTIONS_TABLE_SESSION)
      options_default(global_s_options, oe);
    if (oe->scope & OPTIONS_TABLE_WINDOW)
      options_default(global_w_options, oe);
  }
  libevent = osdep_event_init();

  options_set_number(global_w_options, "monitor-bell", 0);
  options_set_number(global_w_options, "allow-rename", 1);
  options_set_number(global_options, "set-clipboard", 2);
  socket_path = xstrdup("dummy");

  /* Call the missing function */
  server_start(&client, 0, libevent, -1, NULL);

  return 0;
}