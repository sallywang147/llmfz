#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "nxt_task.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct nxt_task_s task;
  task.id = stream.ConsumeIntegral<int>();
  task.priority = stream.ConsumeIntegral<int>();
  task.state = stream.ConsumeIntegral<int>();
  task.data = stream.ConsumeRemainingBytes<uint8_t>().data();

  return nxt_runtime_create(&task);
}