#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "miniz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need to ensure that the size of the data we're trying to add to the archive is less than the size of the input data.
  // We'll reserve a small portion of the input data for the archive name, file name, and comment.
  size_t archive_name_size = stream.ConsumeIntegralInRange<size_t>(0, size / 4);
  size_t file_name_size = stream.ConsumeIntegralInRange<size_t>(0, size / 4);
  size_t comment_size = stream.ConsumeIntegralInRange<size_t>(0, size / 4);

  // Now we know how much data we can use for the file data.
  size_t file_data_size = size - archive_name_size - file_name_size - comment_size;

  // Consume the data for each parameter.
  std::string archive_name = stream.ConsumeBytesAsString(archive_name_size);
  std::string file_name = stream.ConsumeBytesAsString(file_name_size);
  std::string file_data = stream.ConsumeBytesAsString(file_data_size);
  std::string comment = stream.ConsumeBytesAsString(comment_size);

  short compression_level = stream.ConsumeIntegralInRange<short>(0, 10);
  int zip64 = stream.ConsumeBool();

  int status = 0;

  // Call the function under test.
  mz_zip_add_mem_to_archive_file_in_place_v2(
      const_cast<char*>(archive_name.c_str()),
      const_cast<char*>(file_name.c_str()),
      const_cast<char*>(file_data.c_str()),
      file_data.size(),
      const_cast<char*>(comment.c_str()),
      compression_level,
      zip64,
      &status);

  return 0;
}