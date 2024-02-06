#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerInitialize(int * argc, char *** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  int argc = 1;
  char* argv[] = { (char*)"fuzzer", NULL };
  char** argv_ptr = argv;

  LLVMFuzzerInitialize(&argc, &argv_ptr);

  return 0;
}