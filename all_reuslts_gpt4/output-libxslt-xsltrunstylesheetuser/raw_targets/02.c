#include <fuzzer/FuzzedDataProvider.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libxml/parser.h>
#include <libxml/xmlsave.h>
#include <libxml/xmlIO.h>
#include <libxml/xpath.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/HTMLparser.h>
#include <libxml/xmlmemory.h>
#include <libxml/parserInternals.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string xmlContent = stream.ConsumeRandomLengthString();
  xmlDocPtr doc = xmlReadMemory(xmlContent.c_str(), xmlContent.size(), "noname.xml", NULL, 0);
  if (doc == NULL) {
    return 0;
  }

  xsltStylesheetPtr cur = NULL;
  cur = xsltParseStylesheetDoc(xmlCopyDoc(doc, 1));
  if (cur != NULL) {
    xmlDocPtr res = NULL;
    xsltTransformContextPtr ctxt;
    ctxt = xsltNewTransformContext(cur, doc);
    if (ctxt != NULL) {
      res = xsltApplyStylesheetUser(cur, doc, NULL, NULL, NULL, ctxt);
      xsltFreeTransformContext(ctxt);
    }
    xsltFreeStylesheet(cur);
    if (res != NULL) {
      xmlFreeDoc(res);
    }
  }

  xmlFreeDoc(doc);

  return 0;
}