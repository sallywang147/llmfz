#include "ixml.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define kMinInputLength 10
#define kMaxInputLength 5120

int CheckXML(char *buffer) {

  int rc;
  DOMString s;
  IXML_Document *doc = NULL;

  doc = ixmlParseBuffer(buffer);
  if (doc == NULL) {
    return 1;
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

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  int ret;
  char buffer[kMaxInputLength + 1];

  memcpy(buffer, Data, Size);
  buffer[Size] = '\0';

  ret = CheckXML(buffer);
  return ret;
}