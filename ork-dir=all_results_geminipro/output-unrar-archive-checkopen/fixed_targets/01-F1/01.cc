#include <stddef.h>
#include <stdint.h>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <archive.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string name = stream.ConsumeRandomLengthString(1024);
  struct archive *archive;
  archive_check_magic(archive, ARCHIVE_MAGIC);

  return 0;
}