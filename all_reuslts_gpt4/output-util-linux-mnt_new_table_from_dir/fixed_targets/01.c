#include <fuzzer/FuzzedDataProvider.h>
#include <libmount/libmount.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *dirname = const_cast<char*>(str.c_str());

  // Call the function to fuzz
  struct libmnt_table *table = mnt_new_table_from_dir(dirname);

  // Free the table
  if (table) {
    mnt_free_table(table);
  }

  return 0;
}