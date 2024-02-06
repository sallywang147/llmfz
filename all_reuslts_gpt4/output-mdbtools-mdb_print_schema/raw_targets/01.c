#include "mdbtools.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file for output
  FILE* outfile = tmpfile();
  if (outfile == NULL) {
    return 0;
  }

  // Initialize a MdbHandle
  MdbHandle* mdb = mdb_open_buffer((void*)data, size, MDB_NOFLAGS);
  if (mdb == NULL) {
    fclose(outfile);
    return 0;
  }

  // Generate a random table name
  std::string tabname = stream.ConsumeRandomLengthString();
  char* tabname_cstr = const_cast<char*>(tabname.c_str());

  // Generate a random dbnamespace
  std::string dbnamespace = stream.ConsumeRandomLengthString();
  char* dbnamespace_cstr = const_cast<char*>(dbnamespace.c_str());

  // Generate random export options
  int export_options = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  mdb_print_schema(mdb, outfile, tabname_cstr, dbnamespace_cstr, export_options);

  // Cleanup
  mdb_close(mdb);
  fclose(outfile);

  return 0;
}