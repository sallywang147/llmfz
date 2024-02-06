#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  plist_t root_node = NULL;
  plist_from_openstep(reinterpret_cast<const char *>(data), size, &root_node);
  if (root_node == NULL) {
    return 0;
  }

  char *filename = "/tmp/fuzzed.plist";
  int format = PLIST_XML_FORMAT;
  int options = 0;
  int result = plist_write_to_file(root_node, filename, format, options);
  plist_free(root_node);
  return result;
}