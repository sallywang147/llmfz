#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "perfetto/trace_processor/table.h"
#include "perfetto/trace_processor/row_map.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  perfetto::trace_processor::Table table;
  perfetto::trace_processor::RowMap row_map;

  std::vector<int> vec;
  int vec_size = stream.ConsumeIntegralInRange<int>(0, 100);
  for (int i = 0; i < vec_size; i++) {
    vec.push_back(stream.ConsumeIntegral<int>());
  }

  int arg = stream.ConsumeIntegral<int>();

  table.FilterToRowMap(&row_map, &table, &vec, arg);

  return 0;
}