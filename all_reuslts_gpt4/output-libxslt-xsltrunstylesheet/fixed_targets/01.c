#include <fuzzer/FuzzedDataProvider.h>
#include "fuzz.h"

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) {
  return xsltFuzzStylesheetInit();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Extract to user defined object
  struct _xsltStylesheet *style;
  size_t consumed = stream.ConsumeData(&style, sizeof(style));

  struct _xmlDoc *doc;
  consumed = stream.ConsumeData(&doc, sizeof(doc));

  char **params = nullptr; // Not provided by the fuzzer

  char *output = nullptr; // Not provided by the fuzzer

  struct _xmlSAXHandler *SAX;
  consumed = stream.ConsumeData(&SAX, sizeof(SAX));

  struct _xmlOutputBuffer *IObuf;
  consumed = stream.ConsumeData(&IObuf, sizeof(IObuf));

  xsltRunStylesheet(style, doc, params, output, SAX, IObuf);

  return 0;
}