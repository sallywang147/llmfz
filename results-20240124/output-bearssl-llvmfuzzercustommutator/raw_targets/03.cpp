 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" size_t LLVMFuzzerCustomMutator(char *data, size_t size, size_t max_size, int seed) {
  // Do some fuzzing here
  // ...

  // Call the function to be fuzzed
  size_t ret = LLVMFuzzerCustomMutator(data, size, max_size, seed);

  // Do some more fuzzing here
  // ...

  return ret;
}