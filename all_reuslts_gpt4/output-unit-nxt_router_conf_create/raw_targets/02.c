#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "nxt_router.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct nxt_task_s task;
  struct nxt_router_temp_conf_t tmcf;

  std::string str1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  char *start = const_cast<char*>(str1.c_str());

  std::string str2 = stream.ConsumeRemainingBytesAsString();
  char *end = const_cast<char*>(str2.c_str());

  nxt_router_conf_create(&task, &tmcf, start, end);

  return 0;
}