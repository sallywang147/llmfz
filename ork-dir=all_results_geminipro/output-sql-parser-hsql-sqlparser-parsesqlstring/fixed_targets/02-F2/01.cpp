#include "SQLParser.h"
#include <string>

using namespace hsql;

extern "C" {
#include "llvm/FuzzMutate.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  SQLParserResult res;
  SQLParser::parseSQLString(input, &res);
  return 0;
}