#include <fuzzer/FuzzedDataProvider.h>
#include <immer/detail/rbts/node.hpp>
#include <immer/memory.hpp>
#include <tuple>

using namespace immer;
using namespace immer::detail::rbts;

typedef node<int, memory_policy<heap_policy<cpp_heap>, unsafe_refcount_policy, no_lock_policy, no_transience_policy, false, true>, 2u, 2u> NodeType;
typedef regular_pos<NodeType> RegularPosType;
typedef regular_sub_pos RegularSubPosType;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the tuple
  std::tuple<unsigned int, NodeType*, unsigned int, NodeType*> pos_tuple;
  std::get<0>(pos_tuple) = stream.ConsumeIntegral<unsigned int>();
  std::get<1>(pos_tuple) = new NodeType();
  std::get<2>(pos_tuple) = stream.ConsumeIntegral<unsigned int>();
  std::get<3>(pos_tuple) = new NodeType();

  // Initialize the regular_sub_pos
  RegularSubPosType last;
  last.idx = stream.ConsumeIntegral<unsigned int>();
  last.shift = stream.ConsumeIntegral<unsigned int>();
  last.b = stream.ConsumeIntegral<unsigned int>();
  last.mask = stream.ConsumeIntegral<unsigned int>();

  // Initialize the size_t
  size_t e = stream.ConsumeIntegral<size_t>();

  // Call the function to fuzz
  slice_right_mut_visitor<NodeType, true, true>::visit_regular<RegularPosType&>(&pos_tuple, &last, e);

  // Cleanup
  delete std::get<1>(pos_tuple);
  delete std::get<3>(pos_tuple);

  return 0;
}