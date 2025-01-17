#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  int format;
  plist_t root_node = NULL;
  plist_from_memory(reinterpret_cast<char *>(data), size, &root_node, &format);
  plist_free(root_node);

  return 0;
}