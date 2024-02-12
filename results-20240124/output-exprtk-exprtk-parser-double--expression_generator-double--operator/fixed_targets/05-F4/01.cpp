#include <stddef.h>

extern "C" {
#include "exprtk/parser/expression_generator.hpp"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  exprtk::parser<double> parser;
  exprtk::details::expression_node* expression_tree = parser.compile(data, data + size);
  parser.expression_generator()(expression_tree, nullptr, false);
  return 0;
}