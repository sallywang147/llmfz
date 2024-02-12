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