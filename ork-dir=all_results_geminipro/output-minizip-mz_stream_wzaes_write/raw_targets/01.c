#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_mem.h"
#include "mz_strm_wzaes.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string password = stream.ConsumeRemainingBytesAsString();

  void* stream_ptr = mz_stream_wzaes_create(password.c_str());
  if (stream_ptr == nullptr) {
    return 0;
  }

  const std::string input = stream.ConsumeRemainingBytesAsString();
  const int result = mz_stream_wzaes_write(stream_ptr,
                                            reinterpret_cast<char*>(const_cast<char*>(input.c_str())),
                                            input.size());
  mz_stream_wzaes_delete(&stream_ptr);
  return result;
}