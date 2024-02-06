#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "perfetto/trace_processor/table.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create two Table objects
  perfetto::trace_processor::Table table1;
  perfetto::trace_processor::Table table2;

  // Create a vector of RowMap objects
  std::vector<perfetto::trace_processor::RowMap> row_maps;

  // Consume data from the stream to populate the vector
  while (stream.remaining_bytes() > 0) {
    // Consume an index and a size from the stream
    uint32_t index = stream.ConsumeIntegral<uint32_t>();
    uint32_t size = stream.ConsumeIntegral<uint32_t>();

    // Create a RowMap object and add it to the vector
    perfetto::trace_processor::RowMap row_map(index, size);
    row_maps.push_back(row_map);
  }

  // Consume an integer from the stream
  int int_arg = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  table1.Filter(&table2, &table1, &row_maps, int_arg);

  return 0;
}