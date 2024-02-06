#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "libjsonnet.h"
}

struct jsonnet::internal::LocationRange {
  int32_t start_byte;
  int32_t end_byte;
};

struct jsonnet::internal::AST {
  int type;
  jsonnet::internal::LocationRange range;
  std::vector<jsonnet::internal::AST *> children;
};

struct jsonnet::internal::(anonymous namespace)::Interpreter {
  jsonnet::internal::AST *(*parse_expr)(jsonnet::internal::(anonymous namespace)::Interpreter *interp,
                                          jsonnet::internal::LocationRange *range,
                                          std::vector<jsonnet::internal::AST *> *errors);
};

jsonnet::internal::AST *jsonnet::internal::(jsonnet::internal::(anonymous namespace)::Interpreter *interp,
                                               jsonnet::internal::LocationRange *range,
                                               std::vector<jsonnet::internal::AST *> *errors) {
  return nullptr;
}

std::string ConvertJsonnetToJson(const std::string &jsonnet) {
  jsonnet::internal::LocationRange range;
  range.start_byte = 0;
  range.end_byte = jsonnet.size();
  std::vector<jsonnet::internal::AST *> errors;
  jsonnet::internal::AST *ast =
      jsonnet::internal::(jsonnet::internal::(anonymous namespace)::Interpreter *)parse_expr(
          nullptr, &range, &errors);

  std::string json;
  if (ast != nullptr) {
    json = "json";
  }

  jsonnet::internal::AST::free(ast);
  return json;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string fuzz_jsonnet(reinterpret_cast<const char *>(data), size);
  ConvertJsonnetToJson(fuzz_jsonnet);
  return 0;
}