#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>

#include "resip/resip.hpp"

extern "C" {
#include "resip/resip.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  resip::DialogInfoContents* dialog_info_contents =
      new resip::DialogInfoContents();
  resip::XMLCursor* xml_cursor = new resip::XMLCursor();
  const std::string xml_data = stream.ConsumeRemainingBytesAsString();
  xml_cursor->set(xml_data.c_str());
  dialog_info_contents->parseDialog(dialog_info_contents, xml_cursor);
  delete xml_cursor;
  delete dialog_info_contents;
  return 0;
}