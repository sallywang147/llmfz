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

  s = ixmlPrintDocument(doc);
  if (s == NULL || s[0] == '\0') {
    ixmlDocument_free(doc);
    return 1;
  }

  ixmlFreeDOMString(s);
  ixmlDocument_free(doc);

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

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

  IXML_Document *doc = NULL;
  IXML_Node *node = NULL;

  ret = ixmlLoadDocumentEx(filename, &doc);
  if (ret != IXML_SUCCESS) {
    unlink(filename);
    return 0;
  }

  node = ixmlNode_cloneNodeTreeRecursive(ixmlDocument_documentElement(doc), 1);
  ixmlNode_free(node);
  ixmlDocument_free(doc);
  unlink(filename);
  return 0;
}