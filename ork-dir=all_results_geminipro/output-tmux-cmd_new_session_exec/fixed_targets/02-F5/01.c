#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "tmux.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tmux_main_init();
    initialized = true;
  }
  struct cmdq_item item;
  struct cmd cmd;
  cmdq_init(&item);
  cmd_init(&cmd);

  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> cmd_buffer(provider.ConsumeRemainingBytes());
  item.cmd = &cmd;
  item.client = NULL;
  item.flags = 0;
  item.data = cmd_buffer.data();
  item.datalen = cmd_buffer.size();
  cmd_new_session_exec(&cmd, &item);

  cmdq_free(&item);
  cmd_free(&cmd);

  return 0;
}