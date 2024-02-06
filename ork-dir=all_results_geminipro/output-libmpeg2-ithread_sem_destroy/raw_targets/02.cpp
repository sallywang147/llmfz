#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "ithread.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t sem_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* sem = static_cast<char*>(std::malloc(sem_size));
  if (sem == nullptr) {
    return 0;
  }
  memset(sem, 0, sem_size);

  ithread_sem_destroy(sem);
  std::free(sem);

  return 0;
}