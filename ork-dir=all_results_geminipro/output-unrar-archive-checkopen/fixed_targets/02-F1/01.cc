#include <stddef.h>
#include <stdint.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <string>
#include <vector>

extern "C" {
#include "archive.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::vector<std::string> names;
  while (provider.remaining_bytes() > 0) {
    std::string name = provider.ConsumeRandomLengthString();
    names.push_back(name);
  }

  Archive archive;
  for (const auto &name : names) {
    archive.CheckOpen(&archive, const_cast<int *>(name.data()));
  }

  return 0;
}