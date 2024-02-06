#include "ColumnType.h"
#include <ostream>

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  std::stringstream stream;
  ColumnType column_type;
  column_type.parse(input);
  stream << &column_type;
  return 0;
}