#include <fuzzer/FuzzedDataProvider.h>
#include <libraw/libraw.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  LibRaw raw;
  std::exception *stream_exception = nullptr;

  std::string filename = stream.ConsumeRandomLengthString(1024);
  int ret = raw.libraw_openfile_tail(&raw, &stream_exception, filename.c_str());

  if (ret == LIBRAW_SUCCESS) {
    raw.libraw_close(&raw);
  }

  return 0;
}