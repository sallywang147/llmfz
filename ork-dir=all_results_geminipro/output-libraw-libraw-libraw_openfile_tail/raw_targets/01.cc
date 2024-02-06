#include <cstdio>
#include <exception>
#include <fuzzer/FuzzedDataProvider.h>
#include <libraw/libraw.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider data(Data, Size);

  LibRaw *raw = new LibRaw();
  std::exception *stream = nullptr;

  try {
    raw->libraw_open_buffer(data.ConsumeRemainingBytes(), Size);
    raw->libraw_openfile_tail(raw, stream);
  } catch (const std::exception &e) {
    std::fprintf(stderr, "Exception: %s\n", e.what());
  }

  delete raw;
  return 0;
}