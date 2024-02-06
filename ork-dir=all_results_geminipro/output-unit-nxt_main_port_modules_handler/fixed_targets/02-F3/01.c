#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
#include "Fuzz_http.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 1) {
    return 0;
  }

  nxt_task_s task;
  nxt_memzero(&task, sizeof(task));
  task.port = 1;

  nxt_port_recv_msg_s msg;
  nxt_memzero(&msg, sizeof(msg));
  msg.data = (uint8_t *)Data;
  msg.len = Size;

  nxt_main_port_modules_handler(&task, &msg);

  return 0;
}

void nxt_main_port_modules_handler(struct nxt_task_s *task,
                                  struct nxt_port_recv_msg_s *msg) {
  nxt_port_recv_msg_s *recv_msg;
  nxt_port_send_msg_s *send_msg;
  nxt_port_t *port;
  nxt_port_module_t *m;

  port = &task->ports[task->port];
  recv_msg = msg;

  for (m = port->modules; m; m = m->next) {
    if (m->recv_msg) {
      send_msg = m->recv_msg(m, recv_msg);
      if (send_msg) {
        nxt_port_send_msg(task, send_msg);
      }
    }
  }
}

extern "C" void nxt_port_send_msg(struct nxt_task_s *task,
                                 struct nxt_port_send_msg_s *msg) {}

extern "C" void nxt_memzero(void *ptr, size_t size) { memset(ptr, 0, size); }