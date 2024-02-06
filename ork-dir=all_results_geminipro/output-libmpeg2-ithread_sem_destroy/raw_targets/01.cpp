#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t sem_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char* sem = static_cast<char*>(malloc(sem_size));
  stream.ConsumeBytes<char>(sem, sem_size);
  int ret = ithread_sem_destroy(sem);
  free(sem);
  return ret;
}