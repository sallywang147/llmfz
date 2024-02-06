#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // The function XmlInitUnknownEncodingNS requires a memory buffer, a conversion table, a function pointer and a user data pointer.
  // We will generate these inputs using FuzzedDataProvider.

  // mem: a memory buffer
  std::string mem = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  
  // table: an integer array of 256 elements
  int table[256];
  for (int &i : table) {
    i = stream.ConsumeIntegral<int>();
  }

  // convert: a function pointer
  // We define a dummy function for this purpose.
  auto convert = [](void* /*userData*/, const char* /*p*/) -> int { return 0; };
  func_type convert_func = convert;

  // userData: a user data pointer
  char userData[256];
  for (char &c : userData) {
    c = stream.ConsumeIntegral<char>();
  }

  // Call the function with the generated inputs
  struct encoding *result = XmlInitUnknownEncodingNS(mem.data(), table, &convert_func, userData);

  // We don't need to do anything with the result, as we are just testing the function for crashes.
  (void)result;

  return 0;
}