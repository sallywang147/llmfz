#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "mz_zip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare the arguments for the function call
  std::string archive_name = stream.ConsumeRandomLengthString();
  std::string archive_comment = stream.ConsumeRandomLengthString();
  std::string file_name = stream.ConsumeRandomLengthString();
  size_t file_data_size = stream.ConsumeIntegral<size_t>();
  std::string file_comment = stream.ConsumeRandomLengthString();
  short compress_level = stream.ConsumeIntegral<short>();
  int zip_flags = stream.ConsumeIntegral<int>();
  int err = 0;

  // Prepare the file data
  std::vector<char> file_data = stream.ConsumeBytes<char>(file_data_size);

  // Call the function
  mz_zip_add_mem_to_archive_file_in_place_v2(
    archive_name.data(), 
    archive_comment.data(), 
    file_name.data(), 
    file_data_size, 
    file_data.data(), 
    compress_level, 
    zip_flags, 
    &err
  );

  return 0;
}