#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tuple>
#include <vector>

namespace immer {
namespace detail {
namespace rbts {

template <typename Node, bool IsRegular, bool IsRegularLast>
struct slice_right_mut_visitor {
  using node_t = Node;
  using regular_pos_t = regular_pos<node_t>;
  using regular_sub_pos_t = regular_sub_pos;

  void visit_leaf(node_t*) {}
  void visit_inner(node_t*, node_t*) {}
  void visit_regular(regular_pos_t&, regular_sub_pos_t*, size_t) {}
};

template <>
struct slice_right_mut_visitor<Node, IsRegular, IsRegularLast> {
  void visit_leaf(node_t* n) {
    n->inner() = nullptr;
    n->leaf() = nullptr;
  }
  void visit_inner(node_t* n, node_t* n2) {
    n->inner() = n2;
    n2->inner() = nullptr;
    n2->leaf() = nullptr;
  }
  void visit_regular(regular_pos_t& pos, regular_sub_pos_t* last, size_t e) {
    if (pos.pos < e) {
      visit_leaf(pos.node);
    } else {
      visit_inner(pos.node, last->node);
    }
  }
};

}  // namespace rbts
}  // namespace detail
}  // namespace immer

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::tuple<unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*, unsigned int, immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>*> pos;
  immer::detail::rbts::regular_sub_pos last;
  size_t e = provider.ConsumeIntegral<size_t>();
  immer::detail::rbts::slice_right_mut_visitor<immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u>, true, true>::visit_regular<immer::detail::rbts::regular_pos<immer::detail::rbts::node<int, immer::memory_policy<immer::heap_policy<immer::cpp_heap>, immer::unsafe_refcount_policy, immer::no_lock_policy, immer::no_transience_policy, false, true>, 2u, 2u> >&>(
      &pos, &last, e);
  return 0;
}