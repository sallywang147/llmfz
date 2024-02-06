#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cups/ipp.h"
#include "cups/ppd-private.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a buffer for _ppdCreateFromIPP
  std::vector<char> buffer = stream.ConsumeBytes<char>(stream.remaining_bytes() / 2);
  size_t bufsize = buffer.size();

  // Create a fake _ipp_s struct
  struct _ipp_s supported;
  supported.state = IPP_STATE_IDLE;
  supported.version[0] = stream.ConsumeIntegralInRange<char>(0, 255);
  supported.version[1] = stream.ConsumeIntegralInRange<char>(0, 255);
  supported.op = stream.ConsumeIntegralInRange<ipp_op_t>(IPP_OP_CUPS_NONE, IPP_OP_CUPS_MAX);
  supported.request.any = nullptr;
  supported.encoding = IPP_ENCODING_LENGTH_DELIMITED;
  supported.attrs = nullptr;
  supported.last = nullptr;
  supported.current = nullptr;
  supported.curtag = IPP_TAG_ZERO;
  supported.prevtag = IPP_TAG_ZERO;

  // Call the function to fuzz
  _ppdCreateFromIPP(buffer.data(), bufsize, &supported);

  return 0;
}