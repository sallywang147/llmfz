#include <fuzzer/FuzzedDataProvider.h>
#include "SQLParser.h"
#include <sstream>
#include <string>

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a ColumnType object with fuzzed data
  ColumnType column_type;
  column_type.dt = static_cast<DataType>(provider.ConsumeIntegralInRange<int>(0, 6));
  column_type.length = provider.ConsumeIntegral<int>();
  column_type.scale = provider.ConsumeIntegral<int>();

  // Create a stringstream object to pass to the function
  std::stringstream stream;

  // Call the function with the fuzzed data
  hsql::operator<<(&stream, &column_type);

  return 0;
}