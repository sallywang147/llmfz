#include <fuzzer/FuzzedDataProvider.h>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <string>

#include "libcue/libcue.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  
  FILE* tmp_file = tmpfile();
  if (!tmp_file) {
    return 0;
  }

  fwrite(str.data(), 1, str.size(), tmp_file);
  rewind(tmp_file);

  struct Cd* cd = cue_parse_file(tmp_file);

  if (cd) {
    cd_delete(cd);
  }

  fclose(tmp_file);

  return 0;
}