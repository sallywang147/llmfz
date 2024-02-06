#include <fuzzer/FuzzedDataProvider.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include "miniz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  mz_zip_archive archive;
  memset(&archive, 0, sizeof(archive));

  if (!mz_zip_writer_init_heap(&archive, 0, 0)) {
    return 0;
  }

  std::string filename = stream.ConsumeRandomLengthString();
  std::string comment = stream.ConsumeRandomLengthString();
  std::string extrafield = stream.ConsumeRandomLengthString();

  short compression_method = stream.ConsumeIntegralInRange<short>(0, 32767);
  int compression_level = stream.ConsumeIntegralInRange<int>(0, 10);
  int zip64 = stream.ConsumeBool();

  std::vector<uint8_t> file_data = stream.ConsumeRemainingBytes<uint8_t>();
  FILE *file = fmemopen(file_data.data(), file_data.size(), "rb");
  if (!file) {
    mz_zip_writer_end(&archive);
    return 0;
  }

  size_t file_size = file_data.size();
  size_t file_size_written = 0;

  mz_zip_writer_add_cfile(&archive, filename.c_str(), file, file_size, &file_size_written, comment.c_str(), compression_method, compression_level, extrafield.c_str(), extrafield.size(), nullptr, zip64);

  fclose(file);
  mz_zip_writer_end(&archive);

  return 0;
}