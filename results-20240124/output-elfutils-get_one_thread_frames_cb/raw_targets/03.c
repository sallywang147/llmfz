 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "libdwarf.h"
#include "libdwarf_private.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string arg = stream.ConsumeRemainingBytesAsString();
  Dwfl_Thread thread;
  get_one_thread_frames_cb(&thread, const_cast<char*>(arg.c_str()));
  return 0;
}