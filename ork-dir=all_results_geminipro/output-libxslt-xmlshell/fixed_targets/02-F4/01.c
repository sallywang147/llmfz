#include "fuzz.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <libxml/parser.h>
#include <libxml/tree.h>

#ifdef __cplusplus
}
#endif

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xmlShellInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlDocPtr doc = xmlParseMemory(data, size);
  if (doc == NULL) {
    return 0;
  }

  xmlShell(doc, NULL, NULL, NULL);

  xmlFreeDoc(doc);
  return 0;
}