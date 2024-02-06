#include <fuzzer/FuzzedDataProvider.h>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <string>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  struct Log log;

  std::string format_string = stream.ConsumeRandomLengthString();

  va_list args;
  va_start(args, format_string.c_str());
  int result = log_vcommitf(&log, const_cast<char*>(format_string.c_str()), reinterpret_cast<__va_list_tag*>(args));
  va_end(args);

  return 0;
}