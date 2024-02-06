#include <assert.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "tmux.h"

#define FUZZER_MAXLEN 512

struct event_base *libevent;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct cmd * self;
  struct cmdq_item * item;
  int error;

  // Since AFL doesn't support -max_len parameter we have to
  // discard long inputs manually.
  if (size > FUZZER_MAXLEN)
    return 0;

  self = cmd_new(NULL);
  item = cmdq_item_new(NULL, 0);

  // Call the target function
  error = cmd_new_session_exec(self, item);

  // Free resources
  cmd_free(self);
  cmdq_item_free(item);

  return 0;
}

int LLVMFuzzerInitialize(__unused int *argc, __unused char ***argv) {
  const struct options_table_entry *oe;

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

  return 0;
}