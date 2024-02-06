#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "proton/data.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pn_data_t *pn_data = pn_data(0);
  if (pn_data == nullptr) {
    return 0;
  }

  std::string format = stream.ConsumeRandomLengthString();
  __va_list_tag va_list;

  int ret = pn_data_vfill(pn_data, const_cast<char*>(format.c_str()), &va_list);

  pn_data_free(pn_data);

  return 0;
}