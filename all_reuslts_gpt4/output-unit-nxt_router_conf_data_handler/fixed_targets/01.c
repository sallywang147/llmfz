#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "nxt_router.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the task object
  struct nxt_task_s task;
  task.thread = nullptr; // Set to null, as we don't have a valid thread pointer
  task.log = nullptr; // Set to null, as we don't have a valid log pointer

  // Initialize the message object
  struct nxt_port_recv_msg_s msg;

  // Consume data for the message object
  msg.pid = stream.ConsumeIntegral<nxt_pid_t>();
  msg.reply_port = stream.ConsumeIntegral<nxt_port_id_t>();
  msg.port_msg.stream = stream.ConsumeIntegral<nxt_port_id_t>();
  msg.port_msg.pid = stream.ConsumeIntegral<nxt_pid_t>();
  msg.port_msg.type = stream.ConsumeIntegral<uint32_t>();
  msg.port_msg.last = stream.ConsumeIntegral<uint32_t>();
  msg.port_msg.size = stream.ConsumeIntegral<uint32_t>();

  // Consume remaining data for the message payload
  auto remaining_bytes = stream.ConsumeRemainingBytes<uint8_t>();
  msg.port_msg.payload = remaining_bytes.data();

  // Call the target function
  nxt_router_conf_data_handler(&task, &msg);

  return 0;
}