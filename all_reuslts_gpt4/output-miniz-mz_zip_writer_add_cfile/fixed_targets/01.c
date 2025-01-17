#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "miniz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  mz_zip_archive archive;
  mz_zip_zero_struct(&archive);

  if (!mz_zip_writer_init_heap(&archive, 0, 0)) {
    return 0;
  }

  std::string filename = stream.ConsumeRandomLengthString();
  size_t uncomp_size = stream.ConsumeIntegral<size_t>();
  size_t* uncomp_size_ptr = &uncomp_size;
  std::string comment = stream.ConsumeRandomLengthString();
  short level = stream.ConsumeIntegralInRange<short>(0, 9);
  int zip64 = stream.ConsumeBool();
  std::string extrafield = stream.ConsumeRandomLengthString();
  int extrafield_len = stream.ConsumeIntegral<int>();
  std::string aes_key = stream.ConsumeRandomLengthString();
  int aes_key_len = stream.ConsumeIntegral<int>();

  FILE* file = tmpfile();
  if (!file) {
    mz_zip_writer_end(&archive);
    return 0;
  }

  std::vector<uint8_t> file_content = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(file_content.data(), 1, file_content.size(), file);
  rewind(file);

  mz_zip_writer_add_cfile(&archive, filename.c_str(), file, uncomp_size_ptr, comment.c_str(), level, zip64, extrafield.c_str(), extrafield_len, aes_key.c_str(), aes_key_len);

  fclose(file);
  mz_zip_writer_end(&archive);

  return 0;
}