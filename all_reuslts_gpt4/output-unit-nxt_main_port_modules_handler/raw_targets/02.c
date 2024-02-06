#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nxt_main.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct nxt_task_s task;
  struct nxt_port_recv_msg_s msg;

  // Initialize struct nxt_task_s
  task.thread.task = &task;
  task.thread.log_level = stream.ConsumeIntegral<uint32_t>();
  task.thread.ident = stream.ConsumeIntegral<uint32_t>();
  task.thread.handle = stream.ConsumeIntegral<uint32_t>();
  task.thread.epoll = stream.ConsumeIntegral<uint32_t>();
  task.thread.signal = stream.ConsumeIntegral<uint32_t>();
  task.thread.engine = nullptr; // Set to null, as we can't generate a valid engine
  task.thread.time = stream.ConsumeIntegral<uint64_t>();
  task.thread.timer_wheel = nullptr; // Set to null, as we can't generate a valid timer_wheel
  task.thread.timers = nullptr; // Set to null, as we can't generate a valid timers

  // Initialize struct nxt_port_recv_msg_s
  msg.pid = stream.ConsumeIntegral<int>();
  msg.reply_port = stream.ConsumeIntegral<uint32_t>();
  msg.type = stream.ConsumeIntegral<uint32_t>();
  msg.last = stream.ConsumeBool();
  msg.mmap = stream.ConsumeBool();
  msg.fd = stream.ConsumeIntegral<int>();
  msg.stream = stream.ConsumeIntegral<uint32_t>();
  msg.size = stream.ConsumeIntegral<uint32_t>();
  msg.port_msg = nullptr; // Set to null, as we can't generate a valid port_msg

  // Call the function to fuzz
  nxt_main_port_modules_handler(&task, &msg);

  return 0;
}