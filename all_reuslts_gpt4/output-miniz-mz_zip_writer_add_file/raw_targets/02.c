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

  FuzzedDataProvider provider(data, size);

  std::string archive_path = provider.ConsumeRandomLengthString();
  std::string file_path = provider.ConsumeRandomLengthString();
  std::string password = provider.ConsumeRandomLengthString();
  short compression_method = provider.ConsumeIntegral<short>();
  int compression_level = provider.ConsumeIntegral<int>();

  mz_zip_writer_add_file(&zip_archive, archive_path.c_str(), file_path.c_str(), password.c_str(), compression_method, compression_level);

  mz_zip_writer_finalize_archive(&zip_archive);
  mz_zip_writer_end(&zip_archive);

  return 0;
}