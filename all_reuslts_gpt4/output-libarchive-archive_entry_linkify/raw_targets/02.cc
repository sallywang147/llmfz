#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create the link resolver
  struct archive_entry_linkresolver *res = archive_entry_linkresolver_new();
  if (res == nullptr) {
    return 0;
  }
  archive_entry_linkresolver_set_strategy(res, ARCHIVE_FORMAT_CPIO_POSIX);

  // Create the archive entries
  struct archive_entry *e = archive_entry_new();
  struct archive_entry *f = archive_entry_new();
  if (e == nullptr || f == nullptr) {
    archive_entry_linkresolver_free(res);
    if (e != nullptr) archive_entry_free(e);
    if (f != nullptr) archive_entry_free(f);
    return 0;
  }

  // Set the data for the archive entries
  std::string e_data = stream.ConsumeRandomLengthString();
  std::string f_data = stream.ConsumeRandomLengthString();
  archive_entry_set_pathname(e, e_data.c_str());
  archive_entry_set_pathname(f, f_data.c_str());

  // Call the function to fuzz
  archive_entry_linkify(res, &e, &f);

  // Clean up
  archive_entry_linkresolver_free(res);
  archive_entry_free(e);
  archive_entry_free(f);

  return 0;
}