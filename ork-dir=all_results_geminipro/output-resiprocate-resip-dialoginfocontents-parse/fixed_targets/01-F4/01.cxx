#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <resip/resip.h>

extern "C" {
#include <resip/resip.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  resip::DialogInfoContents dialog_info_contents;
  resip::ParseBuffer parse_buffer;
  const std::string text = stream.ConsumeRemainingBytesAsString();
  parse_buffer.append(text.c_str(), text.size());
  dialog_info_contents.parse(&dialog_info_contents, &parse_buffer);
  return 0;
}