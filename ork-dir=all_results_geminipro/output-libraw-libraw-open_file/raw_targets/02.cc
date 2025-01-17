#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string fname = stream.ConsumeRemainingBytesAsString();
  char *fname_ptr = fname.c_str();

  LibRaw libraw;
  libraw.open_file(fname_ptr);
  return 0;
}