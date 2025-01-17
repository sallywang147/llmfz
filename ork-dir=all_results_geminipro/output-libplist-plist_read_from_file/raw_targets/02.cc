#include <plist/plist.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  char *filename = tmpnam(nullptr);
  FILE *fp = fopen(filename, "wb");
  fwrite(data, size, 1, fp);
  fclose(fp);

  char *plist_string;
  int format;
  int result = plist_read_from_file(filename, &plist_string, &format);

  free(filename);
  if (plist_string != NULL) {
    free(plist_string);
  }

  return result;
}