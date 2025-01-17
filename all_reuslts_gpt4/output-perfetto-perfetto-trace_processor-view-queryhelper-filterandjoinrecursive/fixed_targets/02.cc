#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "perfetto/trace_processor/view.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize objects
  perfetto::trace_processor::View::QueryHelper query_helper;
  perfetto::trace_processor::View::TableNode table_node;

  // Consume data to populate TableNode
  table_node.table_id = provider.ConsumeIntegral<uint32_t>();
  table_node.is_root = provider.ConsumeBool();
  table_node.filter = provider.ConsumeRandomLengthString().c_str();
  table_node.join_type = provider.PickValueInArray({perfetto::trace_processor::View::TableNode::JoinType::kLeft,
                                                    perfetto::trace_processor::View::TableNode::JoinType::kInner,
                                                    perfetto::trace_processor::View::TableNode::JoinType::kCross});

  // Call the function to fuzz
  query_helper.FilterAndJoinRecursive(&query_helper, &table_node);

  return 0;
}