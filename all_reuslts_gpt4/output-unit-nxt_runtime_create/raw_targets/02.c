#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nxt_runtime.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct nxt_task_s task;
  task.thread = stream.ConsumeIntegral<uint32_t>();
  task.ident = stream.ConsumeIntegral<uint32_t>();
  task.log = nullptr; // This is a pointer to a struct, we can't generate it with FuzzedDataProvider
  task.thread_pool = nullptr; // This is a pointer to a struct, we can't generate it with FuzzedDataProvider
  task.next = nullptr; // This is a pointer to a struct, we can't generate it with FuzzedDataProvider

  nxt_runtime_create(&task);

  return 0;
}