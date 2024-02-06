#include <plist/plist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  plist_t root_node = NULL;
  plist_from_openstep(reinterpret_cast<const char *>(data), size, &root_node);
  if (root_node == NULL) {
    return 0;
  }

  std::string filename = "/tmp/plist_write_to_file.XXXXXX";
  int fd = mkstemp(&filename[0]);
  if (fd == -1) {
    plist_free(root_node);
    return 0;
  }
  close(fd);

  int format = plist_get_format(root_node);
  if (format == PLIST_FORMAT_INVALID) {
    plist_free(root_node);
    return 0;
  }

  int options = 0;
  plist_write_to_file(filename.c_str(), root_node, options); // Added this line

  plist_free(root_node);
  return 0;
}