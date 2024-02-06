#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <libraw/libraw.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize LibRaw object
  LibRaw RawProcessor;

  // Consume data for the parameters
  std::string img = stream.ConsumeRandomLengthString();
  int nPlanes = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  RawProcessor.crxLoadDecodeLoop(&RawProcessor, const_cast<char*>(img.c_str()), nPlanes);

  return 0;
}