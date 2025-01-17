#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif
#include "SQLParser.h"
#ifdef __cplusplus
}
#endif

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  std::vector<SQLToken> tokens;
  SQLParser::tokenize(input, &tokens);
  return 0;
}