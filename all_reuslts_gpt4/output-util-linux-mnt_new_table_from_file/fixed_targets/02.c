#include <fuzzer/FuzzedDataProvider.h>
#include <libmount/libmount.h>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string filename = stream.ConsumeRandomLengthString();
  
  FILE *fp = tmpfile();
  if (!fp) {
    return 0;
  }
  fwrite(filename.c_str(), 1, filename.size(), fp);
  rewind(fp);

  char filepath[256];
  snprintf(filepath, sizeof(filepath), "/proc/self/fd/%d", fileno(fp));
  
  struct libmnt_table *table = mnt_new_table_from_file(filepath);
  
  if (table) {
    mnt_free_table(table);
  }
  
  fclose(fp);
  
  return 0;
}