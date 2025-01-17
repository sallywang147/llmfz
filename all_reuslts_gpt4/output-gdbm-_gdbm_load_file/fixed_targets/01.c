#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "gdbm.h"

struct dump_file {
  FILE *fp;
  char *name;
  int ungetch;
  int lineno;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  struct dump_file file;
  struct gdbm_file_info dbf;
  struct gdbm_file_info* ofp = nullptr;

  file.fp = tmpfile();
  if (!file.fp) {
    return 0;
  }

  std::vector<uint8_t> buffer = fuzzed_data.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), file.fp);
  rewind(file.fp);

  int replace = fuzzed_data.ConsumeBool();
  int meta_mask = fuzzed_data.ConsumeIntegral<int>();

  _gdbm_load_file(&file, &dbf, &ofp, replace, meta_mask);

  fclose(file.fp);

  return 0;
}