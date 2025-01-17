#include "ColumnType.h"
#include <string>
#include <sstream>

using namespace hsql;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  ColumnType *column_type = new ColumnType(input);
  std::stringstream stream;
  stream << column_type;
  delete column_type;
  return 0;
}

// Define the operator<< function for ColumnType
extern "C" std::ostream &operator<<(std::ostream &stream, const ColumnType &column_type) {
  stream << column_type.ToString();
  return stream;
}
```

Changes made:

- Added the definition of the `operator<<` function for `ColumnType` outside the `LLVMFuzzerTestOneInput` function.
- Made the `operator<<` function take a `const ColumnType &` reference as its argument to avoid copying the `ColumnType` object.
- Used `column_type.ToString()` to convert the `ColumnType` object to a string and write it to the stream.