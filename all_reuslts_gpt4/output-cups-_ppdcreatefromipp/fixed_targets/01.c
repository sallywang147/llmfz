#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cups/ipp.h"
#include "cups/ppd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the buffer and its size
  size_t bufsize = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> buffer(bufsize);

  // Define and initialize the _ipp_s struct
  struct _ipp_s supported;
  supported.state = static_cast<ipp_state_t>(stream.ConsumeIntegral<int>());
  supported.version[0] = stream.ConsumeIntegral<int8_t>();
  supported.version[1] = stream.ConsumeIntegral<int8_t>();
  supported.op = stream.ConsumeIntegral<int16_t>();
  supported.request_id = stream.ConsumeIntegral<int32_t>();

  // Call the target function
  _ppdCreateFromIPP(buffer.data(), bufsize, &supported);

  return 0;
}