#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "mz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string from the data stream
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *archive_name = const_cast<char *>(str.c_str());

  int mode = stream.ConsumeIntegral<int>();
  int err = 0;

  mz_zip_validate_file_archive(archive_name, mode, &err);

  return 0;
}