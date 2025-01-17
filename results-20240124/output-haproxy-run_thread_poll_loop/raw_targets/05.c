 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" char* run_thread_poll_loop(char * data) {
  FuzzedDataProvider stream(data, 1);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  return strdup(text.c_str());
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char * output = run_thread_poll_loop((char*)data);
  free(output);
  return 0;
}