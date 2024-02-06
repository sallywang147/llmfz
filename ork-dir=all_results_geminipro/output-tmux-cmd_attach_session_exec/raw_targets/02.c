#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tmux.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tmux_server_init(0, false);
    initialized = true;
  }

  struct cmd *self = (struct cmd *)malloc(sizeof(struct cmd));
  struct cmdq_item *item = (struct cmdq_item *)malloc(sizeof(struct cmdq_item));

  FuzzedDataProvider provider(data, size);

  item->client = (struct client *)malloc(sizeof(struct client));
  item->client->session = (struct session *)malloc(sizeof(struct session));
  item->client->session->curw = (struct window *)malloc(sizeof(struct window));
  item->client->session->curw->active = (struct window_pane *)malloc(sizeof(struct window_pane));

  item->cmd = (struct cmd_list *)malloc(sizeof(struct cmd_list));
  item->cmd->entry = (struct cmd_entry *)malloc(sizeof(struct cmd_entry));

  self->entry = item->cmd->entry;

  self->entry->args = (char **)malloc(sizeof(char *));
  self->entry->args[0] = (char *)malloc(provider.ConsumeIntegralInRange<size_t>(0, 100));
  provider.ConsumeBytes(self->entry->args[0], provider.ConsumeIntegralInRange<size_t>(0, 100));
  self->entry->args[1] = (char *)malloc(provider.ConsumeIntegralInRange<size_t>(0, 100));
  provider.ConsumeBytes(self->entry->args[1], provider.ConsumeIntegralInRange<size_t>(0, 100));
  self->entry->args[2] = (char *)malloc(provider.ConsumeIntegralInRange<size_t>(0, 100));
  provider.ConsumeBytes(self->entry->args[2], provider.ConsumeIntegralInRange<size_t>(0, 100));

  self->entry->narg = 3;

  int result = cmd_attach_session_exec(self, item);

  free(self->entry->args[0]);
  free(self->entry->args[1]);
  free(self->entry->args[2]);
  free(self->entry->args);
  free(self->entry);
  free(item->cmd);
  free(item->client->session->curw->active);
  free(item->client->session->curw);
  free(item->client->session);
  free(item->client);
  free(item);
  free(self);

  return result;
}