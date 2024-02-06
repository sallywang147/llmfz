#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  plist_t root_node = NULL;
  int plist_format;
  plist_from_memory(reinterpret_cast<const char *>(data), size, &root_node,
                    &plist_format);
  plist_free(root_node);

  return 0;
}