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
    tmux_main_init(0);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  struct cmdq_item item;
  item.flags = 0;
  item.client = NULL;
  item.target_session = NULL;
  item.target_window = NULL;
  item.cmd = NULL;

  std::vector<char*> args;
  while (provider.remaining_bytes() > 0) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 256);
    auto arg_data = provider.ConsumeBytes<char>(arg_size);
    char* arg = reinterpret_cast<char*>(malloc(arg_size + 1));
    memcpy(arg, arg_data.data(), arg_size);
    arg[arg_size] = '\0';
    args.push_back(arg);
  }
  item.argc = args.size();
  item.argv = args.data();

  struct cmd* self = cmd_new_session_exec;
  self->entry(self, &item);

  for (size_t i = 0; i < item.argc; i++) {
    free(item.argv[i]);
  }

  return 0;
}