#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"

extern "C" {
#include <libarchive/archive.h>
#include <libarchive/archive_entry.h>
}

extern "C" {
struct archive;
bool WCheckOpen(const int* name_len);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    archive_init();
    initialized = true;
  }
  Archive* archive = archive_read_new();
  if (archive == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
  archive_read_support_compression_all(archive);
  archive_read_support_format_all(archive);
  if (archive_read_open_memory(archive, next_input.data(), next_input.size(), 1)
      != ARCHIVE_OK) {
    archive_read_free(archive);
    return 0;
  }

  int name_len = 0;
  while (archive_read_next_header2(archive, &name_len) == ARCHIVE_OK) {
    std::vector<char> name(name_len + 1);
    if (archive_read_data(archive, name.data(), name_len) != name_len) {
      archive_read_free(archive);
      return 0;
    }
    name[name_len] = '\0';
    bool ret = WCheckOpen(&name_len);
    if (ret) {
      archive_read_data_skip(archive);
    }
  }

  archive_read_close(archive);
  archive_read_free(archive);

  return 0;
}