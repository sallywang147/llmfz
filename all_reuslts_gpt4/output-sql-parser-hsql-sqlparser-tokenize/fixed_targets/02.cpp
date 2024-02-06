#include "SQLParser.h"
#include <string>
#include <vector>

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  std::vector<std::string> tokens;
  SQLParser::tokenize(&input, &tokens);
  return 0;
}