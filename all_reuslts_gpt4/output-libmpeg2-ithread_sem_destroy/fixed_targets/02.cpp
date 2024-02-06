#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ithread.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string sem = stream.ConsumeRandomLengthString();
  char *sem_ptr = const_cast<char*>(sem.c_str());

  // Call the function to fuzz
  int result = ithread_sem_destroy(sem_ptr);

  return 0;
}