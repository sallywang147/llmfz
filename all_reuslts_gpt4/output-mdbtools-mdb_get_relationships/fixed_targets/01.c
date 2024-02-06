#include <fuzzer/FuzzedDataProvider.h>

#include "mdbtools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Split the input data into three parts for dbnamespace, tablename and mdb buffer
  size_t dbnamespace_size = stream.ConsumeIntegralInRange<size_t>(0, size / 3);
  std::string dbnamespace = stream.ConsumeBytesAsString(dbnamespace_size);

  size_t tablename_size = stream.ConsumeIntegralInRange<size_t>(0, size / 3);
  std::string tablename = stream.ConsumeBytesAsString(tablename_size);

  std::vector<uint8_t> mdb_buffer = stream.ConsumeRemainingBytes<uint8_t>();

  // Open the mdb handle
  MdbHandle *mdb = mdb_open_buffer(mdb_buffer.data(), mdb_buffer.size(), MDB_NOFLAGS);
  if (mdb) {
    // Call the target function
    char *relationships = mdb_get_relationships(mdb, const_cast<char*>(dbnamespace.c_str()), const_cast<char*>(tablename.c_str()));
    free(relationships);
    mdb_close(mdb);
  }

  return 0;
}