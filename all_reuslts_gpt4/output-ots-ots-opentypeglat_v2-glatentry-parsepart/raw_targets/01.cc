#include <fuzzer/FuzzedDataProvider.h>
#include <ots.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data to create a buffer
  std::vector<uint8_t> buffer_data = stream.ConsumeRemainingBytes<uint8_t>();
  ots::Buffer table(buffer_data.data(), buffer_data.size());

  // Create a GlatEntry object
  ots::OpenTypeGLAT_v2::GlatEntry glat_entry;

  // Call the function to be fuzzed
  glat_entry.ParsePart(&glat_entry, &table);

  return 0;
}