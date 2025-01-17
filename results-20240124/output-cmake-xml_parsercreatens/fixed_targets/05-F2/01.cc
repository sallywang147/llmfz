#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <expat.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <libxml/xmlversion.h>
#include <libxml/xmlIO.h>
#include <libxml/HTMLparser.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/debugXML.h>
#include <libxml/xmlregexp.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlstring.h>
#include <libxml/dict.h>
#include <libxml/xmlerror.h>
#include <libxml/globals.h>
#include <libxml/xmlmemory.h>
#include <libxml/SAX.h>
#include <libxml/valid.h>
#include <libxml/xmlIO.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlregexp.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlschemasparser.h>
#include <libxml/xmlschemavalid.h>
#include <libxml/xmlregexp.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemasparser.h>
#include <libxml/xmlschemavalid.h>
#include <libxml/xmldtd.h>
#include <libxml/xmlunicode.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlschemasparser.h>
#include <libxml/xmlschemavalid.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlschemasparser.h>
#include <libxml/xmlschemavalid.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  FuzzedDataProvider stream(data, size);
  char *encoding = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 16)).c_str();
  char sep = stream.ConsumeIntegral<char>();

  XML_Parser parser = XML_ParserCreateNS(encoding, sep);
  if (parser)
    XML_ParserFree(parser);

  return 0;
}