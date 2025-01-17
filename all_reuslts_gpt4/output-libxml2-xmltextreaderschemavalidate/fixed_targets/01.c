#include <fuzzer/FuzzedDataProvider.h>

#include <libxml/xmlreader.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  xmlTextReaderPtr reader = xmlReaderForMemory((const char*)data, size, NULL, NULL, 0);
  if (!reader) {
    return 0;
  }

  // Consume half of the remaining data for xsd
  size_t xsd_size = stream.remaining_bytes() / 2;
  std::string xsd = stream.ConsumeBytesAsString(xsd_size);

  xmlTextReaderSchemaValidate(reader, (char *)xsd.c_str());

  xmlFreeTextReader(reader);

  return 0;
}