 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <dwfl/dwfl.h>
#include <dwfl/libdwfl.h>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<uint8_t> bytes = std::vector<uint8_t>(data, data + size);
  const char *data_ptr = reinterpret_cast<const char *>(bytes.data());
  Dwfl *dwfl = dwfl_begin(data_ptr);
  if (!dwfl) {
    return 0;
  }
  dwfl_report_errors(dwfl, stderr);
  dwfl_report_end(dwfl, stderr);

  struct Dwfl_Thread *thread = dwfl_get_thread(dwfl, 0);
  if (!thread) {
    dwfl_end(dwfl);
    return 0;
  }

  std::string arg_str;
  FuzzedDataProvider stream(data, size);
  size_t arg_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  for (size_t i = 0; i < arg_size; ++i) {
    arg_str += stream.ConsumeIntegral<uint8_t>();
  }
  const char *arg = arg_str.c_str();

  get_one_thread_frames_cb(thread, const_cast<char *>(arg));
  dwfl_end(dwfl);
  return 0;
}