#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "perfetto/trace_processor/query_executor.h"
#include "perfetto/trace_processor/row_map.h"
#include "perfetto/trace_processor/table.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize QueryExecutor, RowMap, Table, and vector objects
  perfetto::trace_processor::QueryExecutor query_executor;
  perfetto::trace_processor::RowMap row_map;
  perfetto::trace_processor::Table table;
  std::vector<int64_t> vector;

  // Populate the vector with random data
  while (stream.remaining_bytes() > 0) {
    vector.push_back(stream.ConsumeIntegral<int64_t>());
  }

  // Call the function to be fuzzed
  query_executor.FilterLegacy(&row_map, &table, &vector);

  return 0;
}