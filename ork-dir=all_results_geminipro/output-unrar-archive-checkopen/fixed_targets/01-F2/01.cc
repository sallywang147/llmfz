#include <stddef.h>
#include <stdint.h>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

#include <archive.h>

extern "C" {
void Archive::CheckOpen(Archive *this, int *Name);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string name = stream.ConsumeRandomLengthString(1024);
  struct archive *archive;
  archive_check_magic(archive, ARCHIVE_MAGIC);

  Archive::CheckOpen(archive, NULL);

  return 0;
}