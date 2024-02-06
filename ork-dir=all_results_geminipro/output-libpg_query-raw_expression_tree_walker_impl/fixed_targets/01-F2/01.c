#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

struct Node {};
typedef void (*func_type)(void*);

extern "C" {
bool raw_expression_tree_walker_impl(struct Node*, func_type*, char*);
}

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t node_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
  struct Node* node =
      static_cast<struct Node*>(std::malloc(sizeof(struct Node) * node_size));
  if (node == nullptr) {
    return 0;
  }
  memset(node, 0, sizeof(struct Node) * node_size);
  const size_t func_type_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
  func_type* func_type = static_cast<func_type*>(
      std::malloc(sizeof(func_type) * func_type_size));
  if (func_type == nullptr) {
    std::free(node);
    return 0;
  }
  memset(func_type, 0, sizeof(func_type) * func_type_size);
  const size_t char_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
  char* c_str = static_cast<char*>(std::malloc(char_size));
  if (c_str == nullptr) {
    std::free(node);
    std::free(func_type);
    return 0;
  }
  memset(c_str, 0, char_size);
  raw_expression_tree_walker_impl(node, func_type, c_str);
  std::free(node);
  std::free(func_type);
  std::free(c_str);
  return 0;
}
}