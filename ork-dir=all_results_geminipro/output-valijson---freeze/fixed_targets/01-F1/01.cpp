#include <stdexcept>
#include <unistd.h>

#include <document.h>
#include <valijson/adapters/rapidjson_adapter.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/utils/rapidjson_utils.hpp>

extern "C" {
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
}

using valijson::Schema;
using valijson::SchemaParser;
using valijson::adapters::RapidJsonAdapter;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3)
    return 0;
  char input_file[256];
  sprintf(input_file, "/tmp/libfuzzer.json");
  FILE *fp = fopen(input_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  rapidjson::Document schemaDocument;
  if (!valijson::utils::loadDocument(input_file, schemaDocument)) {
    return 1;
  }

  Schema schema;
  SchemaParser parser;
  RapidJsonAdapter schemaDocumentAdapter(schemaDocument);
  try {
    parser.populateSchema(schemaDocumentAdapter, schema);
  } catch (std::exception &e) {
    unlink(input_file);
    return 1;
  }

  unlink(input_file);

  rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > value;
  valijson::adapters::GenericRapidJsonValue<rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > > genericValue(value);
  valijson::adapters::GenericRapidJsonArrayValueIterator iterator;
  std::__function::__base *base = genericValue.freeze(&iterator);
  return 1;
}