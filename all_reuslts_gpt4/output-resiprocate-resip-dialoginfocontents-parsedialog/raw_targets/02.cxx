#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "rutil/XMLCursor.hxx"
#include "resip/stack/DialogInfoContents.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xmlString = stream.ConsumeRemainingBytesAsString();
  resip::Data xmlData(xmlString.c_str());

  resip::XMLCursor xmlCursor(xmlData);
  resip::DialogInfoContents dialogInfoContents;

  resip::DialogInfoContents::parseDialog(&dialogInfoContents, &xmlCursor);

  return 0;
}