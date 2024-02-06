#include "SQLParser.h"
#include "fuzzer/FuzzedDataProvider.h"
#include <iostream>
#include <sstream>

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Define and initialize column_type
  ColumnType column_type;
  column_type.name = stream.ConsumeRandomLengthString().c_str();
  column_type.length = stream.ConsumeIntegral<int>();
  column_type.scale = stream.ConsumeIntegral<int>();
  column_type.precision = stream.ConsumeIntegral<int>();
  column_type.dt = stream.ConsumeEnum<DataType>();
  
  // Define and initialize std::ostream
  std::ostringstream oss;

  // Call the function
  hsql::operator<<(&oss, &column_type);

  return 0;
}