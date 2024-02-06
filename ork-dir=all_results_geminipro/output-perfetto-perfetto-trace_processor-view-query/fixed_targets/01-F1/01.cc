#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "perfetto/trace_processor/table.h"
#include "perfetto/trace_processor/view.h"

extern "C" {
#include "perfetto/trace_processor/trace_processor.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  perfetto::trace_processor::Table table;
  perfetto::trace_processor::View view;
  std::vector<perfetto::protos::pbzero::TracePacket> packets;
  std::vector<perfetto::protos::pbzero::TracePacket> packets_to_skip;
  perfetto::trace_processor::BitVector bit_vector;

  view.Query(&table, &view, &packets, &packets_to_skip, &bit_vector);
  return 0;
}