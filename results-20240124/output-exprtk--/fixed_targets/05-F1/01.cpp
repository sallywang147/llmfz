#include <cstdint>
#include <string>

#include "exprtk.hpp"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::string expression(reinterpret_cast<const char*>(data), size);
  exprtk::details::node_allocator allocator;
  exprtk::details::expression_node<float>* node =
      allocator.allocate_rrr<exprtk::details::vec_binop_vecvec_node<float,
                                                                 exprtk::details::div_op<
                                                                     float>>>(
          nullptr, nullptr, nullptr, nullptr);
  return 0;
}
}