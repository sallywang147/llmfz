#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "resip/stack/DialogInfoContents.hxx"
#include "rutil/XMLCursor.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create a DialogInfoContents object
  resip::DialogInfoContents dialogInfoContents;

  // Create an XMLCursor object
  std::string xml_string = provider.ConsumeRemainingBytesAsString();
  resip::Data xml_data(xml_string.c_str());
  resip::XMLCursor xmlCursor(xml_data);

  // Call the function to fuzz
  resip::DialogInfoContents::parseDialog(&dialogInfoContents, &xmlCursor);

  return 0;
}