#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nxt_task.h"
#include "nxt_router_temp_conf.h"
#include "nxt_str.h"
#include "nxt_http_action.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the required structures
  struct nxt_task_s task;
  struct nxt_router_temp_conf_t tmcf;
  struct nxt_str_t pass;

  // Fill the structures with fuzzed data
  if (stream.remaining_bytes() > sizeof(task)) {
    stream.ConsumeData(&task, sizeof(task));
  } else {
    return 0;
  }

  if (stream.remaining_bytes() > sizeof(tmcf)) {
    stream.ConsumeData(&tmcf, sizeof(tmcf));
  } else {
    return 0;
  }

  // Create a string for pass
  std::string pass_str = stream.ConsumeRemainingBytesAsString();
  pass.length = pass_str.size();
  pass.start = (u_char *)pass_str.c_str();

  // Call the target function
  struct nxt_http_action_s* action = nxt_http_action_create(&task, &tmcf, &pass);

  return 0;
}