#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int scanopt_usage(char ** scanner, struct _IO_FILE * fp, char * usage);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for 'scanner' parameter
  std::vector<std::string> scannerStrings;
  while (stream.remaining_bytes() > 0) {
    scannerStrings.push_back(stream.ConsumeRandomLengthString());
    if (scannerStrings.size() == 100) {
      // Limit the number of strings to avoid excessive memory consumption.
      break;
    }
  }
  std::vector<char*> scanner;
  for (auto& str : scannerStrings) {
    scanner.push_back(const_cast<char*>(str.c_str()));
  }
  scanner.push_back(nullptr);  // Null-terminate the array.

  // Use a dummy file for 'fp' parameter
  struct _IO_FILE *fp = tmpfile();
  if (!fp) {
    return 0;
  }

  // Consume data for 'usage' parameter
  std::string usage = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  scanopt_usage(scanner.data(), fp, const_cast<char*>(usage.c_str()));

  // Clean up
  fclose(fp);

  return 0;
}