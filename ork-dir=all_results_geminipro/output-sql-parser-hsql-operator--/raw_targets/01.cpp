#include "ColumnType.h"
#include <string>

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  ColumnType *column_type = new ColumnType(input);
  std::ostream *stream = new std::stringstream();
  *stream << column_type;
  delete stream;
  delete column_type;
  return 0;
}