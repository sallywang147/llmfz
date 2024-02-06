#include <fuzzer/FuzzedDataProvider.h>
#include <libxml/tree.h>
#include <libxml/xmlIO.h>
#include <libxml/xmlsave.h>
#include <libxml/xmlversion.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare the inputs for xmlShell function
  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
  xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "root");
  xmlDocSetRootElement(doc, root_node);

  std::string filename = stream.ConsumeRandomLengthString();
  xmlParserInputBufferPtr input = xmlParserInputBufferCreateMem(stream.ConsumeRemainingBytesAsString().c_str(), size, XML_CHAR_ENCODING_NONE);

  // Call xmlShell function
  xmlShell(doc, const_cast<char*>(filename.c_str()), input->readcallback, stdout);

  // Cleanup
  xmlFreeDoc(doc);
  xmlFreeParserInputBuffer(input);

  return 0;
}