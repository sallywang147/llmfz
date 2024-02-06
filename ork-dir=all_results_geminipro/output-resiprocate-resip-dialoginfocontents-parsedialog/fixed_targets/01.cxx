#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "resip/resip.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string xml_input = stream.ConsumeRemainingBytesAsString();
  resip::XMLCursor cursor(xml_input.c_str());

  resip::DialogInfoContents dialog_info_contents;
  dialog_info_contents.parseDialog(&dialog_info_contents, &cursor);
  return 0;
}