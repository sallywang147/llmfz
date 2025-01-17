#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "libjsonnet.h"
}

int ImportCallback(void *ctx, const char *base, const char *rel, char **found_here, char **buf, size_t *buflen) {
  // Don't load file and mark it as failure.
  *buf = NULL;
  *buflen = 0;
  return 1;
}

struct jsonnet::internal::AST *
jsonnet::internal::EvaluateSnippetStream(jsonnet::internal::Interpreter *interp,
                                         jsonnet::internal::LocationRange *location,
                                         std::vector<jsonnet::internal::ImportSpec> *import_specs,
                                         const char *snippet) {
  jsonnet::internal::String str(snippet);
  return jsonnet::internal::EvaluateSnippet(interp, location, import_specs, str);
}

struct jsonnet::internal::AST *
jsonnet::internal::EvaluateSnippet(jsonnet::internal::Interpreter *interp,
                                     jsonnet::internal::LocationRange *location,
                                     std::vector<jsonnet::internal::ImportSpec> *import_specs,
                                     jsonnet::internal::String str) {
  jsonnet::internal::String *ret =
      jsonnet::internal::Evaluate(interp, location, import_specs, str);
  if (ret == NULL) {
    return nullptr;
  }
  jsonnet::internal::AST *ast = jsonnet::internal::ParseJson(ret);
  jsonnet::internal::Free(ret);
  return ast;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string fuzz_jsonnet(reinterpret_cast<const char *>(data), size);
  jsonnet::internal::Interpreter interp;
  jsonnet::internal::LocationRange location;
  std::vector<jsonnet::internal::ImportSpec> import_specs;
  import_specs.emplace_back(jsonnet::internal::ImportSpec{
      "fuzz.jsonnet", nullptr, ImportCallback, nullptr});
  jsonnet::internal::AST *ast =
      jsonnet::internal::EvaluateSnippetStream(&interp, &location, &import_specs,
                                                fuzz_jsonnet.c_str());
  jsonnet::internal::Free(ast);
  return 0;
}