#include <fuzzer/FuzzedDataProvider.h>

#include "mdbtools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);
  
  // Consume a string for table_name
  std::string tableName = stream.ConsumeRandomLengthString();
  
  // Consume an integer for obj_type
  int objType = stream.ConsumeIntegral<int>();
  
  // Open a buffer for mdb
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  
  if (mdb) {
    // Call the function to fuzz
    mdb_read_table_by_name(mdb, (char *)tableName.c_str(), objType);
    mdb_close(mdb);
  }
  
  return 0;
}