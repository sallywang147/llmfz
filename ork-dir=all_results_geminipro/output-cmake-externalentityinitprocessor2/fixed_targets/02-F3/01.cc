#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  XML_Parser parser = XML_ParserCreate(nullptr);
  if (parser == nullptr) {
    return 0;
  }

  const size_t text_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t context_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t encoding_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* text = reinterpret_cast<char*>(malloc(text_length + 1));
  char* context = reinterpret_cast<char*>(malloc(context_length + 1));
  char* encoding = reinterpret_cast<char*>(malloc(encoding_length + 1));
  if (text == nullptr || context == nullptr || encoding == nullptr) {
    free(text);
    free(context);
    free(encoding);
    XML_ParserFree(parser);
    return 0;
  }
  stream.ConsumeBytes(text, text_length);
  stream.ConsumeBytes(context, context_length);
  stream.ConsumeBytes(encoding, encoding_length);
  text[text_length] = '\0';
  context[context_length] = '\0';
  encoding[encoding_length] = '\0';

  int result = XML_ExternalEntityInitParser(parser, context, encoding, &text);
  // Call the function `externalEntityInitProcessor2`
  int result2 = externalEntityInitProcessor2(parser, context, encoding, &text);
  XML_ParserFree(parser);
  free(text);
  free(context);
  free(encoding);
  return result && result2;
}

int externalEntityInitProcessor2(XML_Parser parser, const XML_Char* context,
                                 const XML_Char* encoding, const XML_Char** text) {
  // Implement the logic for `externalEntityInitProcessor2` here.
  return 0;
}