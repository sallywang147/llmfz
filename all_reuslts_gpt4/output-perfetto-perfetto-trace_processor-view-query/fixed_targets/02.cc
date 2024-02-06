#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "src/trace_processor/trace_processor.h"
#include "src/trace_processor/types/trace_processor_context.h"
#include "src/trace_processor/storage/trace_storage.h"
#include "src/trace_processor/db/table.h"
#include "src/trace_processor/db/view.h"
#include "src/trace_processor/db/bit_vector.h"

using perfetto::trace_processor::TraceProcessor;
using perfetto::trace_processor::TraceProcessorContext;
using perfetto::trace_processor::TraceStorage;
using perfetto::trace_processor::Table;
using perfetto::trace_processor::View;
using perfetto::trace_processor::BitVector;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a TraceProcessorContext
  TraceProcessorContext context;

  // Create a TraceStorage and assign it to the context
  context.storage.reset(new TraceStorage());

  // Create a Table and a View
  Table table(&context);
  View view(&context);

  // Create two vectors
  std::vector<uint32_t> vector1;
  std::vector<uint32_t> vector2;

  // Create a BitVector
  BitVector bit_vector;

  // Populate the vectors and the BitVector with data from the fuzzer
  while (stream.remaining_bytes() > 0) {
    vector1.push_back(stream.ConsumeIntegral<uint32_t>());
    vector2.push_back(stream.ConsumeIntegral<uint32_t>());
    bit_vector.Append(stream.ConsumeBool());
  }

  // Call the function to fuzz
  view.Query(&table, &view, &vector1, &vector2, &bit_vector);

  return 0;
}