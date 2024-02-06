#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "jsonnet.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  jsonnet::internal::(anonymous namespace)::Interpreter interpreter;
  jsonnet::internal::LocationRange locationRange;
  std::vector<jsonnet::internal::AST*> astVector;

  // We need to initialize the vector with AST pointers. 
  // For simplicity, let's create an empty AST and duplicate it.
  jsonnet::internal::AST* ast = new jsonnet::internal::AST();
  size_t vectorSize = stream.ConsumeIntegralInRange<size_t>(0, 10);
  for (size_t i = 0; i < vectorSize; i++) {
    astVector.push_back(ast);
  }

  jsonnet::internal::AST* result = jsonnet::internal::(interpreter, &locationRange, &astVector);

  // Cleanup
  delete result;
  delete ast;

  return 0;
}