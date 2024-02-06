#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "../../src/common/clib-package.h"
#include "../../src/common/list.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a list
  struct list_t *list = list_new();
  if (!list) {
    return 0;
  }

  // Add a few items to the list
  for (int i = 0; i < 5; i++) {
    struct clib_package_t *pkg = (struct clib_package_t *)malloc(sizeof(struct clib_package_t));
    if (!pkg) {
      list_destroy(list);
      return 0;
    }
    list_node_t *node = list_node_new(pkg);
    if (!node) {
      free(pkg);
      list_destroy(list);
      return 0;
    }
    list_rpush(list, node);
  }

  // Create a directory string
  std::string dir = stream.ConsumeRandomLengthString();
  int verbose = stream.ConsumeBool();

  // Call the function to be fuzzed
  install_packages(list, (char *)dir.c_str(), verbose);

  // Free memory
  list_destroy(list);

  return 0;
}