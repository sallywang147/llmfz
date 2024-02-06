#include <fuzzer/FuzzedDataProvider.h>
#include <libmount/libmount.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string dir_name = stream.ConsumeRandomLengthString();
  
  // Call the function with the fuzzed inputs
  struct libmnt_table *table = mnt_new_table_from_dir(const_cast<char*>(dir_name.c_str()));

  // Cleanup
  mnt_free_table(table);

  return 0;
}