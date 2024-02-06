#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct dump_file file;
  struct gdbm_file_info dbf;
  struct gdbm_file_info *ofp;

  file.name = provider.ConsumeRandomLengthString().c_str();
  file.fp = tmpfile();
  if (file.fp == NULL) {
    return 0;
  }
  std::vector<uint8_t> file_content = provider.ConsumeRemainingBytes<uint8_t>();
  fwrite(file_content.data(), 1, file_content.size(), file.fp);
  rewind(file.fp);

  dbf.header.av_size = provider.ConsumeIntegral<unsigned int>();
  dbf.header.dir_size = provider.ConsumeIntegral<unsigned int>();
  dbf.header.dir_bits = provider.ConsumeIntegral<unsigned int>();
  dbf.header.block_size = provider.ConsumeIntegral<unsigned int>();
  dbf.header.dir = provider.ConsumeIntegral<unsigned int>();
  dbf.header.bucket_size = provider.ConsumeIntegral<unsigned int>();
  dbf.header.bucket = provider.ConsumeIntegral<unsigned int>();
  dbf.header.header_magic = provider.ConsumeIntegral<unsigned int>();
  dbf.header.block_magic = provider.ConsumeIntegral<unsigned int>();
  dbf.header.dir_magic = provider.ConsumeIntegral<unsigned int>();
  dbf.header.av_count = provider.ConsumeIntegral<unsigned int>();

  int replace = provider.ConsumeBool();
  int meta_mask = provider.ConsumeIntegral<int>();

  _gdbm_load_file(&file, &dbf, &ofp, replace, meta_mask);

  fclose(file.fp);

  return 0;
}