#include "fuzz.h"

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) {
  return xsltFuzzStylesheetInit();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the stylesheet
  std::string stylesheet_str = stream.ConsumeRandomLengthString();
  xsltStylesheetPtr style = xsltFuzzStylesheetParse(stylesheet_str.c_str(), stylesheet_str.size());
  if (style == nullptr) {
    return 0;
  }

  // Extract the remaining bytes for the document
  std::vector<uint8_t> doc_bytes = stream.ConsumeRemainingBytes<uint8_t>();
  xmlDocPtr doc = xsltFuzzDocumentParse(doc_bytes.data(), doc_bytes.size());
  if (doc == nullptr) {
    xsltFuzzStylesheetFree(style);
    return 0;
  }

  // Apply the stylesheet to the document
  xmlDocPtr result = xsltApplyStylesheet(style, doc, nullptr);

  // Clean up
  xsltFuzzDocumentFree(doc);
  xsltFuzzStylesheetFree(style);
  if (result != nullptr) {
    xsltFuzzDocumentFree(result);
  }

  return 0;
}