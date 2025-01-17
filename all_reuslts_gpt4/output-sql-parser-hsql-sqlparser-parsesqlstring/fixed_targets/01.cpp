#include "SQLParser.h"
#include <fuzzer/FuzzedDataProvider.h>

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string sql = stream.ConsumeRandomLengthString();
  SQLParserResult result;
  SQLParser::parseSQLString(&sql, &result);
  return 0;
}