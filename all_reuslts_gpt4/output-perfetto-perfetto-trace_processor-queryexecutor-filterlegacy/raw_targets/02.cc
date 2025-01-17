#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

#include "perfetto/trace_processor/query_executor.h"
#include "perfetto/trace_processor/row_map.h"
#include "perfetto/trace_processor/table.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  perfetto::trace_processor::RowMap row_map;
  perfetto::trace_processor::Table table;
  std::vector<int> vec;

  // Initialize QueryExecutor
  perfetto::trace_processor::QueryExecutor query_executor;

  // Call the function to fuzz
  query_executor.FilterLegacy(&row_map, &table, &vec);

  return 0;
}