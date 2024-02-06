#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "mz_zip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string str = stream.ConsumeRandomLengthString();
  char *archive_name = const_cast<char*>(str.c_str());
  int archive_mode = stream.ConsumeIntegral<int>();
  int archive_error = 0;

  mz_zip_validate_file_archive(archive_name, archive_mode, &archive_error);
  
  return 0;
}