#include <fuzzer/FuzzedDataProvider.h>
#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a new XML parser
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  // Extract the first string
  std::string str1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  char *str1_ptr = const_cast<char *>(str1.c_str());

  // Extract the second string
  std::string str2 = stream.ConsumeRemainingBytesAsString();
  char *str2_ptr = const_cast<char *>(str2.c_str());

  // Prepare a char pointer array
  char *argv[] = { str1_ptr, str2_ptr, NULL };

  // Call the function to be fuzzed
  externalEntityInitProcessor2((XML_ParserStruct *)parser, str1_ptr, str2_ptr, argv);

  // Clean up
  XML_ParserFree(parser);

  return 0;
}