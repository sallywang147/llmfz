#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tmux.h"

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
```

The issue is that the `tmux.h` header is included twice, once with and once without the `extern "C"` wrapper. This can cause linker errors, as the compiler may not be able to determine which definition of the `tmux` functions to use.

To fix this, remove the `#include "tmux.h"` line from the top of the file and keep the `extern "C"`-wrapped `#include` inside the `extern "C"` block. This will ensure that the `tmux` functions are only included once, and that the linker will be able to find the correct definitions.