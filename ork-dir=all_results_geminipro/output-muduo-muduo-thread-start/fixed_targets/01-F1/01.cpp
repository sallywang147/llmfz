#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "muduo/base/Thread.h"

extern "C" {
#include "llvm/ADT/StringRef.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  llvm::StringRef str(data, size);
  muduo::Thread t(str.str());
  t.start(&t);
  return 0;
}