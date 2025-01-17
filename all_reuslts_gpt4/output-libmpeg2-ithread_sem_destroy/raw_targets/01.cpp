#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "ithread.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. We use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *sem = const_cast<char *>(str.c_str());

  // Call the function under test
  int result = ithread_sem_destroy(sem);

  return 0;
}