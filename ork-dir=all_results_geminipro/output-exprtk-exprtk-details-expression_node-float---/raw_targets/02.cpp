#include <cstdint>
#include <string>

#define exprtk_enable_range_runtime_checks
#include "exprtk.hpp"

namespace exprtk { namespace details {
  template <typename T, typename Op>
  struct vec_binop_vecvec_node {
    typedef exprtk::details::expression_node<vec_binop_vecvec_node<T, Op> > node_type;

    static node_type *allocate_rrr(std::allocator *alloc, int *n,
                                   node_type **a, node_type **b) {
      return exprtk::details::node_allocator::allocate_rrr<vec_binop_vecvec_node<T, Op> >(alloc, n, a, b);
    }
  };
}}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  exprtk::details::vec_binop_vecvec_node<float, exprtk::details::div_op<float> >::allocate_rrr(nullptr, nullptr, nullptr, nullptr);
  return 0;
}