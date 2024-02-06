#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "perfetto/trace_processor/table.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  perfetto::trace_processor::Table table1;
  perfetto::trace_processor::Table table2;
  std::vector<uint8_t> vector = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());
  int int_arg = stream.ConsumeIntegral<int>();

  table1.Filter(&table2, &table2, &vector, int_arg);

  return 0;
}