#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 10000));
  char *ptr = reinterpret_cast<char *>(bytes.data());
  size_t count = bytes.size();

  FILE *stream_fp = fopen("/dev/null", "w");
  fmt::v10::detail::fwrite_fully(ptr, count, stream_fp);
  fclose(stream_fp);

  return 0;
}