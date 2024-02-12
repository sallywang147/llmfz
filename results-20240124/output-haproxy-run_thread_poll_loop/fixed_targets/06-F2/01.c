#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>
#include <fuzzer/libfuzzer_macro.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" char* run_thread_poll_loop(char* data) {
  FuzzedDataProvider stream(reinterpret_cast<const uint8_t*>(data), 1000);
  std::string fuzzed_data_str = stream.ConsumeBytesAsString(1000);
  char* fuzzed_data = new char[fuzzed_data_str.size() + 1];
  std::strcpy(fuzzed_data, fuzzed_data_str.c_str());

  return run_thread_poll_loop(fuzzed_data);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  run_thread_poll_loop(reinterpret_cast<char*>(const_cast<uint8_t*>(data)));
  return 0;
}