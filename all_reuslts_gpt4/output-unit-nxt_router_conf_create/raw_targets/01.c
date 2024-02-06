#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nxt_router.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize task and tmcf
  struct nxt_task_s task;
  struct nxt_router_temp_conf_t tmcf;

  // Consume data for start and end pointers
  std::string start_str = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string end_str = stream.ConsumeRemainingBytesAsString();
  char* start = const_cast<char*>(start_str.c_str());
  char* end = const_cast<char*>(end_str.c_str());

  // Call the target function
  nxt_router_conf_create(&task, &tmcf, start, end);

  return 0;
}