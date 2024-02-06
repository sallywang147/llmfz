#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  plist_t root_node = NULL;
  plist_from_openstep(reinterpret_cast<const char *>(data), size, &root_node);
  if (root_node == NULL) {
    return 0;
  }

  plist_write_to_stream(reinterpret_cast<char *>(root_node), stdout, PLIST_XML_FORMAT,
                        PLIST_OPTION_NO_COMMENTS);
  plist_free(root_node);

  return 0;
}