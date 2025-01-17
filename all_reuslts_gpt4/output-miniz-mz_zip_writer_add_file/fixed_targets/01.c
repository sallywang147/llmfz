#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "miniz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  mz_zip_archive zip_archive;
  mz_zip_zero_struct(&zip_archive);

  if (!mz_zip_writer_init_heap(&zip_archive, 0, 0)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string archive_name = stream.ConsumeRandomLengthString();
  std::string file_name = stream.ConsumeRandomLengthString();
  std::string comment = stream.ConsumeRandomLengthString();
  short compression_method = stream.ConsumeIntegral<short>();
  int level = stream.ConsumeIntegral<int>();

  mz_zip_writer_add_file(&zip_archive, archive_name.c_str(), file_name.c_str(), comment.c_str(), compression_method, level);

  mz_zip_writer_finalize_archive(&zip_archive);
  mz_zip_writer_end(&zip_archive);

  return 0;
}