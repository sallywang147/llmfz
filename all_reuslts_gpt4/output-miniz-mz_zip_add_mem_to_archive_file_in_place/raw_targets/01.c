#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "miniz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need at least two bytes for archive name and file name
  if (size < 2) {
    return 0;
  }

  // Split the data into two parts: archive name and file name
  size_t archiveNameSize = stream.ConsumeIntegralInRange<size_t>(1, size - 1);
  std::string archiveName = stream.ConsumeBytesAsString(archiveNameSize);
  std::string fileName = stream.ConsumeRemainingBytesAsString();

  // Create dummy data to be added to the archive
  std::string fileData = "dummy data";
  size_t fileDataSize = fileData.size();

  // Define the comment and level variables
  std::string comment = "comment";
  short commentSize = static_cast<short>(comment.size());
  int level = 6; // Compression level

  // Call the target function
  mz_zip_add_mem_to_archive_file_in_place(archiveName.c_str(), fileName.c_str(), fileData.c_str(), fileDataSize, comment.c_str(), commentSize, level);

  return 0;
}