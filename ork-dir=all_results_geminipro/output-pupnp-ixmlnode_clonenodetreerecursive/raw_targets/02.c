#include "ixml.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define kMinInputLength 10
#define kMaxInputLength 5120

int CheckXML(char *filename) {

  int rc;
  DOMString s;
  IXML_Document *doc = NULL;

  rc = ixmlLoadDocumentEx(filename, &doc);
  if (rc != IXML_SUCCESS) {
    return rc;
  }

  struct _IXML_Node *node = ixmlNode_cloneNodeTreeRecursive(ixmlDocument_root(doc), 1);

  s = ixmlPrintNode(node);
  if (s == NULL || s[0] == '\0') {
    ixmlDocument_free(doc);
    return 1;
  }

  ixmlFreeDOMString(s);
  ixmlNode_free(node);
  ixmlDocument_free(doc);

  return 0;
}

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  int ret;
  char filename[256];

  sprintf(filename, "/tmp/libfuzzer.%d", getpid());
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }

  fwrite(Data, Size, 1, fp);
  fclose(fp);

  ret = CheckXML(filename);
  unlink(filename);
  return ret;
}