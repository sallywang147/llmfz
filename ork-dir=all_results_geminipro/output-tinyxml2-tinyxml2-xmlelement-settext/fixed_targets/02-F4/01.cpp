#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "tinyxml2.h"

extern "C" {
#include "llvm/ADT/ArrayRef.h"
#include "llvm/FuzzMutate/FuzzMutate.h"
}

using namespace llvm;
using namespace tinyxml2;

static size_t MutateTinyXML(uint8_t *Data, size_t Size, size_t MaxBytesToMutate) {
  // Parse the XML document.
  XMLDocument doc;
  doc.Parse((char *)Data, Size);

  // Get the root element.
  XMLElement *root = doc.RootElement();
  if (!root)
    return 0;

  // Mutate the root element's text.
  ArrayRef<uint8_t> TextData(Data, Size);
  MutateStringField(TextData, &root->Value(), MaxBytesToMutate);

  // Serialize the mutated XML document.
  std::string Out;
  doc.Print(&Out);

  // Copy the mutated XML document back to the input buffer.
  memcpy(Data, Out.c_str(), Out.size());

  // Return the size of the mutated XML document.
  return Out.size();
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  // Mutate the XML document.
  size_t MutatedSize = MutateTinyXML((uint8_t *)Data, Size, 1024);

  // If the XML document was mutated, return the mutated size.
  if (MutatedSize)
    return MutatedSize;

  // Otherwise, return the original size.
  return Size;
}