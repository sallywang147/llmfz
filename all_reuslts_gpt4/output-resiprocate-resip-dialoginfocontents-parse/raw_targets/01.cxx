#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "resip/stack/DialogInfoContents.hxx"
#include "resip/stack/ParseBuffer.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  resip::DialogInfoContents dialogInfoContents;
  std::string bufferString = stream.ConsumeRemainingBytesAsString();
  resip::Data bufferData(bufferString.c_str());
  resip::ParseBuffer parseBuffer(bufferData);

  try {
    resip::DialogInfoContents::parse(&dialogInfoContents, &parseBuffer);
  } catch (...) {
    // Ignore all exceptions.
  }

  return 0;
}