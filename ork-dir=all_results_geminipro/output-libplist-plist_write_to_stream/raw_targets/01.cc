#include <plist/plist.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  plist_t root_node = NULL;
  plist_from_openstep(reinterpret_cast<const char *>(data), size, &root_node);
  if (root_node == NULL) {
    return 0;
  }

  FILE *fp = fopen("/dev/null", "w");
  if (fp == NULL) {
    plist_free(root_node);
    return 0;
  }

  int result = plist_write_to_stream(root_node, fp, PLIST_XML_FORMAT_V1_0, 0);
  fclose(fp);
  plist_free(root_node);

  return result;
}