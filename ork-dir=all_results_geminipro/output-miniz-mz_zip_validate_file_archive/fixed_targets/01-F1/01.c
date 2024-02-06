#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_mem.h"
#include "mz_zip.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input_file = stream.ConsumeRemainingBytesAsString();
  int error_code;
  int result = mz_zip_validate_file_archive(
      const_cast<char*>(input_file.c_str()), input_file.size(), &error_code);
  return result;
}