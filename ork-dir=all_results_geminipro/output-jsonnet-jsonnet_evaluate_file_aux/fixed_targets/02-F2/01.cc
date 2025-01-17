#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" {
#include "libjsonnet.h"
}

int ImportCallback(void *ctx, const char *base, const char *rel, char **found_here, char **buf, size_t *buflen) {
  // Don't load file and mark it as failure.
  *buf = NULL;
  *buflen = 0;
  return 1;
}

std::string ConvertJsonnetToJson(const std::string &jsonnet) {
  JsonnetVm *jvm = jsonnet_make();
  jsonnet_import_callback(jvm, ImportCallback, jvm);
  int error = 0;
  char *res = jsonnet_evaluate_snippet_stream(jvm, /*filename=*/"", jsonnet.c_str(), &error);

  std::string json;
  if (error == 0 && res != nullptr) {
    json = res;
  }

  if (res) {
    jsonnet_realloc(jvm, res, 0);
  }
  jsonnet_destroy(jvm);
  return json;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string fuzz_jsonnet(reinterpret_cast<const char *>(data), size);

  JsonnetVm *jvm = jsonnet_make();
  jsonnet_import_callback(jvm, ImportCallback, jvm);
  int error = 0;
  char *res = jsonnet_evaluate_snippet_stream(jvm, /*filename=*/"", fuzz_jsonnet.c_str(), &error);

  std::string json;
  if (error == 0 && res != nullptr) {
    json = res;
  }

  if (res) {
    jsonnet_realloc(jvm, res, 0);
  }
  jsonnet_destroy(jvm);
  return 0;
}