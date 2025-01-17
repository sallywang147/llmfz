#include <cstdint>
#include <string>

#include "exprtk.hpp"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const std::string expression(reinterpret_cast<const char*>(data), size);
  exprtk::details::expression_node<float>* node = nullptr;
  exprtk::details::node_allocator allocator;
  allocator.allocate_rrr<exprtk::details::vec_binop_vecvec_node<float, exprtk::details::div_op<float> >, exprtk::details::operator_type const, exprtk::details::expression_node<float>*, exprtk::details::expression_node<float>*>(nullptr, nullptr, &node, &node);
  return 0;
}
}

namespace exprtk {
namespace details {
template <typename T, typename Op, typename Left, typename Right>
expression_node<T>* node_allocator::allocate_rrr(std::allocator* alloc, int* pcount, expression_node<T>** pnode, expression_node<T>** pnode2) const {
  return new (alloc) vec_binop_vecvec_node<T, Op>(*pnode, *pnode2);
}
}  // namespace details
}  // namespace exprtk