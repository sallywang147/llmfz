#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "perfetto/trace_processor/view.h"

using perfetto::trace_processor::View;

struct TableNode {
  int table_id;
  int parent_id;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a QueryHelper object
  View::QueryHelper query_helper;

  // Create a TableNode object
  TableNode table_node;
  table_node.table_id = stream.ConsumeIntegral<int>();
  table_node.parent_id = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  query_helper.FilterAndJoinRecursive(&query_helper, &table_node);

  return 0;
}