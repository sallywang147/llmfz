#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "muduo/base/Thread.h"

extern "C" {
#include "llvm/FuzzMutator.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  muduo::Thread thread;
  thread.start();  // Fix: Remove the &
  return 0;
}