#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <algorithm>
}

extern "C" char* run_thread_poll_loop(char * data) {
  FuzzedDataProvider stream((const uint8_t *)data, 0);
  const uint8_t data_size = stream.ConsumeIntegral<uint8_t>();
  char *data_ptr = new char[data_size];
  stream.ConsumeBytes(data_ptr, data_size);
  return data_ptr;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char *data_ptr = run_thread_poll_loop((char *)data);
  delete [] data_ptr;
  return 0;
}