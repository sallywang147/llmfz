#include <fuzzer/FuzzedDataProvider.h>
#include <liblouis.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string tableList = stream.ConsumeRandomLengthString();
  
  // Call the function with the fuzzed inputs
  char** result = lou_getEmphClasses(const_cast<char*>(tableList.c_str()));

  // Free the memory allocated by lou_getEmphClasses
  for (int i = 0; result[i] != NULL; i++) {
    free(result[i]);
  }
  free(result);

  return 0;
}