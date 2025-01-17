#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "muduo/base/Thread.h"

void threadFunc() {
  // Do nothing in this thread function
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  muduo::Thread thread(threadFunc);
  thread.start(&thread);
  thread.join();
  return 0;
}