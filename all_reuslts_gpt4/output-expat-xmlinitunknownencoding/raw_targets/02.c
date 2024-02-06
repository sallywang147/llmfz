#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "expat.h"

struct MyData {
  char* mem;
  int* table;
  func_type* convert;
  char* userData;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for the parameters
  const size_t mem_size = stream.ConsumeIntegralInRange<size_t>(0, 50);
  std::string mem_str = stream.ConsumeBytesAsString(mem_size);
  char* mem = const_cast<char*>(mem_str.c_str());

  const size_t table_size = stream.ConsumeIntegralInRange<size_t>(0, 50);
  std::vector<int> table_vector = stream.ConsumeIntegralVector<int>(table_size);
  int* table = table_vector.data();

  func_type* convert = nullptr;

  const size_t userData_size = stream.ConsumeIntegralInRange<size_t>(0, 50);
  std::string userData_str = stream.ConsumeBytesAsString(userData_size);
  char* userData = const_cast<char*>(userData_str.c_str());

  // Call the function
  struct encoding* result = XmlInitUnknownEncoding(mem, table, convert, userData);

  return 0;
}