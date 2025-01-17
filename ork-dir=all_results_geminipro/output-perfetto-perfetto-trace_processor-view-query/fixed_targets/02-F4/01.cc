#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <memory>
#include <vector>

#include "perfetto/protos/pbzero/trace_record.pb.h"
#include "perfetto/protos/pbzero/data_source_descriptor.pb.h"
#include "perfetto/trace_processor/bit_vector.h"
#include "perfetto/trace_processor/table.h"
#include "perfetto/trace_processor/view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  auto table = std::make_unique<perfetto::trace_processor::Table>();
  auto view = std::make_unique<perfetto::trace_processor::View>();
  std::vector<perfetto::protos::pbzero::TraceRecord> records;
  std::vector<perfetto::protos::pbzero::DataSourceDescriptor> data_sources;
  auto bit_vector = std::make_unique<perfetto::trace_processor::BitVector>();
  view->Query(table.get(), view.get(), &records, &data_sources, bit_vector.get());
  return 0;
}