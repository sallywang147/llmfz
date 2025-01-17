#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "tinyxml2.h"

extern "C" {
#include "llvm/FuzzMutate.h"
}

using namespace tinyxml2;

static size_t MutateXMLElement(uint8_t* Data, size_t Size, size_t MaxSize) {
  if (Size < 1) return 0;
  XMLDocument doc;
  doc.Parse((char*)Data, Size);
  XMLElement* root = doc.FirstChildElement();
  if (!root) return 0;
  std::string text((char*)Data, Size);
  size_t pos = 0;
  while ((pos = text.find("<", pos)) != std::string::npos) {
    size_t end_pos = text.find(">", pos);
    if (end_pos == std::string::npos) break;
    std::string tag = text.substr(pos, end_pos - pos + 1);
    if (tag.find("<") != std::string::npos) break;
    if (tag.find(">") != std::string::npos) break;
    if (tag.find("\"") != std::string::npos) break;
    if (tag.find("'") != std::string::npos) break;
    if (tag.find(" ") != std::string::npos) break;
    if (tag.find("=") != std::string::npos) break;
    if (tag.find("/") != std::string::npos) break;
    if (tag.find("?") != std::string::npos) break;
    if (tag.find("!") != std::string::npos) break;
    if (tag.find("-") != std::string::npos) break;
    if (tag.find("_") != std::string::npos) break;
    if (tag.find(":") != std::string::npos) break;
    if (tag.find(".") != std::string::npos) break;
    if (tag.size() > 32) break;
    XMLElement* elem = doc.NewElement(tag.c_str());
    if (!elem) break;
    root->InsertEndChild(elem);
    pos = end_pos + 1;
  }
  XMLPrinter printer;
  doc.Print(&printer);
  std::string result = printer.CStr();
  if (result.size() > MaxSize) return 0;
  memcpy(Data, result.c_str(), result.size());
  return result.size();
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
  if (Size < 1) return 0;
  uint8_t* MutatedData = (uint8_t*)malloc(Size);
  size_t NewSize = MutateXMLElement(MutatedData, Size, Size);
  if (NewSize == 0) {
    free(MutatedData);
    return 0;
  }
  // Insert a new text node into the XML document.
  XMLDocument doc;
  doc.Parse((char*)MutatedData, NewSize);
  XMLElement* root = doc.FirstChildElement();
  if (!root) {
    free(MutatedData);
    return 0;
  }
  XMLElement* new_text = doc.NewText("Hello, world!");
  if (!new_text) {
    free(MutatedData);
    return 0;
  }
  root->InsertNewText(new_text);
  XMLPrinter printer;
  doc.Print(&printer);
  std::string result = printer.CStr();
  if (result.size() > Size) {
    free(MutatedData);
    return 0;
  }
  memcpy(Data, result.c_str(), result.size());
  free(MutatedData);
  return result.size();
}