#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlwriter.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  xmlDocPtr document;

  xmlInitParser();
  xmlKeepBlanksDefault(0);
  xmlLoadExtDtdDefaultValue = XML_DETECT_IDS | XML_COMPLETE_ATTRS;
  document = xmlReadMemory((const char *)data, size, "noname.xml", NULL, 0);
  if (document == NULL) {
    xmlCleanupParser();
    return 0;
  }

  xmlNodePtr node = xmlDocGetRootElement(document);
  if (node == NULL) {
    xmlFreeDoc(document);
    xmlCleanupParser();
    return 0;
  }

  xmlCopyNodeList(node);

  xmlFreeDoc(document);
  xmlCleanupParser();
  return 0;
}