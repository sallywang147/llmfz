#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pg_query.h"

typedef bool (*func_type)(struct Node *, char *);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a dummy function for the func_type parameter
  auto dummy_func = [](struct Node* node, char* arg) -> bool { return true; };

  // Consume data for the Node and char* parameters
  Node node;
  size_t consumed = stream.ConsumeData(&node, sizeof(Node));
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *ptr = str.c_str();

  raw_expression_tree_walker_impl(&node, dummy_func, ptr);

  return 0;
}