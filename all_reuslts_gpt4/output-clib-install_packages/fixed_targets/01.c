#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common/clib-package.h"
#include "deps/list/list.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a list
  struct list_t *list = list_new();

  // Generate a random number of packages to add to the list
  size_t num_packages = stream.ConsumeIntegralInRange<size_t>(0, 10);
  for (size_t i = 0; i < num_packages; ++i) {
    // Generate a random package
    struct clib_package_t *pkg = (struct clib_package_t *)malloc(sizeof(struct clib_package_t));
    if (!pkg) {
      return 0;
    }

    // Fill the package with random data
    pkg->name = strdup(stream.ConsumeRandomLengthString().c_str());
    pkg->version = strdup(stream.ConsumeRandomLengthString().c_str());
    pkg->repo = strdup(stream.ConsumeRandomLengthString().c_str());
    pkg->description = strdup(stream.ConsumeRandomLengthString().c_str());
    pkg->install = strdup(stream.ConsumeRandomLengthString().c_str());

    // Add the package to the list
    list_rpush(list, list_node(pkg));
  }

  // Generate a random directory and verbosity level
  char *dir = strdup(stream.ConsumeRandomLengthString().c_str());
  int verbose = stream.ConsumeBool();

  // Call the function to be tested
  install_packages(list, dir, verbose);

  // Free the directory
  free(dir);

  // Free the list and its contents
  list_iterator_t *it = list_iterator_new(list, LIST_HEAD);
  list_node_t *node;
  while ((node = list_iterator_next(it))) {
    struct clib_package_t *pkg = (struct clib_package_t *)node->val;
    free(pkg->name);
    free(pkg->version);
    free(pkg->repo);
    free(pkg->description);
    free(pkg->install);
    free(pkg);
  }
  list_iterator_destroy(it);
  list_destroy(list);

  return 0;
}