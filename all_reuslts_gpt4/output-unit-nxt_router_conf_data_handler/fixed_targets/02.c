#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "nxt_router.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct nxt_task_s task;
  struct nxt_port_recv_msg_s msg;

  // Initialize the task and msg structures with fuzzed data.
  stream.ConsumeData(&task, sizeof(task));
  stream.ConsumeData(&msg, sizeof(msg));

  // Call the function under test.
  nxt_router_conf_data_handler(&task, &msg);

  return 0;
}