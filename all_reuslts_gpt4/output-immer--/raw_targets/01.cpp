#include <fuzzer/FuzzedDataProvider.h>
#include <immer/detail/rbts/node.hpp>
#include <immer/memory.hpp>
#include <immer/heap_policy.hpp>
#include <tuple>

using namespace immer;
using namespace immer::detail::rbts;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the required types
  using NodeType = node<int, memory_policy<heap_policy<cpp_heap>, unsafe_refcount_policy, no_lock_policy, no_transience_policy, false, true>, 2u, 2u>;
  using TupleType = std::tuple<unsigned int, NodeType*, unsigned int, NodeType*>;
  using VisitorType = slice_right_mut_visitor<NodeType, true, true>;
  using PosType = regular_pos<NodeType>;

  // Consume data to initialize the required parameters
  unsigned int ui1 = stream.ConsumeIntegral<unsigned int>();
  unsigned int ui2 = stream.ConsumeIntegral<unsigned int>();
  NodeType* node1 = new NodeType();
  NodeType* node2 = new NodeType();
  TupleType pos(ui1, node1, ui2, node2);
  regular_sub_pos last;
  size_t e = stream.ConsumeIntegral<size_t>();

  // Call the function to fuzz
  VisitorType().visit_regular<PosType>(pos, &last, e);

  // Clean up
  delete node1;
  delete node2;

  return 0;
}