#include <fuzzer/FuzzedDataProvider.h>
#include <perfetto/trace_processor/table.h>
#include <perfetto/trace_processor/row_map.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  perfetto::trace_processor::Table table;
  perfetto::trace_processor::RowMap row_map;
  std::vector<uint8_t> vector = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());
  int int_arg = stream.ConsumeIntegral<int>();

  table.FilterToRowMap(&row_map, &table, &vector, int_arg);

  return 0;
}