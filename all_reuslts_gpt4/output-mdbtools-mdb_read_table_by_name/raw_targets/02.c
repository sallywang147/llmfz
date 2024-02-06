#include <fuzzer/FuzzedDataProvider.h>
#include "mdbtools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Consume a string for the table name
  std::string tableName = stream.ConsumeRandomLengthString();
  char *tableNamePtr = const_cast<char*>(tableName.c_str());

  // Consume an integer for the object type
  int objType = stream.ConsumeIntegral<int>();

  // Open a buffer and read the table by name
  MdbHandle *mdb = mdb_open_buffer((void *)data, size, MDB_NOFLAGS);
  if (mdb) {
    mdb_read_table_by_name(mdb, tableNamePtr, objType);
    mdb_close(mdb);
  }
  
  return 0;
}