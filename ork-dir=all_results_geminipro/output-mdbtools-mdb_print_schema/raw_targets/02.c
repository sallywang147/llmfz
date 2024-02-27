#include <fuzzer/FuzzedDataProvider.h>
#include "mdbtools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    FuzzedDataProvider stream(Data, Size);

    std::string tabname = stream.ConsumeRemainingBytesAsString();
    std::string dbnamespace = stream.ConsumeRemainingBytesAsString();
    int export_options = stream.ConsumeIntegral<int>();

    mdb_print_schema(mdb, stdout, const_cast<char *>(tabname.c_str()),
                     const_cast<char *>(dbnamespace.c_str()), export_options);
    mdb_close(mdb);
  }
  return 0;
}