#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "nodes/nodes.h"
}

// Dummy function to pass to raw_expression_tree_walker_impl
bool dummy_func(struct Node *node, char *context) {
  return false;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create dummy Node
  struct Node node;
  node.type = (NodeTag)stream.ConsumeIntegral<int>();

  // Create dummy context
  std::string context = stream.ConsumeRemainingBytesAsString();

  // Call the function
  raw_expression_tree_walker_impl(&node, dummy_func, const_cast<char*>(context.c_str()));

  return 0;
}