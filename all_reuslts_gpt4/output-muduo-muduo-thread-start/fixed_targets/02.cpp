#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "muduo/base/Thread.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  muduo::Thread thread([]() {}, "FuzzingThread");
  thread.start(&thread);
  thread.join();
  return 0;
}