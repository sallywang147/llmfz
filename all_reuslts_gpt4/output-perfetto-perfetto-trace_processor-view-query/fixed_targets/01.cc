#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "src/trace_processor/trace_processor.h"
#include "src/trace_processor/db/view.h"
#include "src/trace_processor/db/bit_vector.h"
#include "src/trace_processor/db/table.h"

using namespace perfetto::trace_processor;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize trace processor
  std::unique_ptr<TraceProcessor> tp = TraceProcessor::Create();

  // Create a table
  Table table;

  // Create a view
  View view(&table);

  // Create vectors
  std::vector<uint32_t> vec1, vec2;

  // Create a bit vector
  BitVector bv;

  // Call the target function
  view.Query(&table, &view, &vec1, &vec2, &bv);

  return 0;
}