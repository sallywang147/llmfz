#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement *root = doc.NewElement("root");
  doc.InsertFirstChild(root);

  while (stream.remaining_bytes() > 0) {
    std::string comment = stream.ConsumeRandomLengthString();
    root->InsertNewComment(comment.c_str());
  }

  return 0;
}