#include <fuzzer/FuzzedDataProvider.h>
#include <libexif/exif-entry.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ExifEntry
  ExifEntry* entry = new ExifEntry();
  if (!entry) {
    return 0;
  }

  // Fill ExifEntry with random data
  entry->tag = stream.ConsumeIntegral<ExifTag>();
  entry->format = stream.ConsumeIntegral<ExifFormat>();
  entry->components = stream.ConsumeIntegral<unsigned long>();
  entry->size = stream.ConsumeIntegralInRange<unsigned int>(0, 100);
  entry->data = new unsigned char[entry->size];
  if (!entry->data) {
    delete entry;
    return 0;
  }
  auto bytes = stream.ConsumeBytes<unsigned char>(entry->size);
  memcpy(entry->data, bytes.data(), bytes.size());

  // Get random indent value
  int indent = stream.ConsumeIntegralInRange<int>(0, 10);

  // Call target function
  exif_entry_dump(entry, indent);

  // Cleanup
  delete[] entry->data;
  delete entry;

  return 0;
}