#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "tinyxml2/tinyxml2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinyxml2::XMLDocument doc;
  tinyxml2::XMLElement* root = doc.NewElement("Root");

  std::string comment = stream.ConsumeRemainingBytesAsString();
  root->InsertNewComment(comment.c_str());

  return 0;
}