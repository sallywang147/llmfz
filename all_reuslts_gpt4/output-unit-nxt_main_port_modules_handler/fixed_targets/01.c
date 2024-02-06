#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "nxt_main.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct nxt_task_s task;
  struct nxt_port_recv_msg_s msg;

  // We can't predict the exact structure of nxt_task_s and nxt_port_recv_msg_s,
  // but we can fill them with random data.
  stream.ConsumeData(&task, sizeof(task));
  stream.ConsumeData(&msg, sizeof(msg));

  nxt_main_port_modules_handler(&task, &msg);

  return 0;
}