#include "ixml.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define kMinInputLength 10
#define kMaxInputLength 5120

extern "C" {
#include <libxml/parser.h>
#include <libxml/tree.h>
}

int CheckXML(char *buffer) {

  int rc;
  DOMString s;
  IXML_Document *doc = NULL;

  rc = ixmlParseBufferEx(buffer, &doc);
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
  char *buffer = (char *)malloc(Size + 1);
  if (!buffer) {
    return 0;
  }

  memcpy(buffer, Data, Size);
  buffer[Size] = '\0';

  ret = CheckXML(buffer);
  free(buffer);
  return ret;
}