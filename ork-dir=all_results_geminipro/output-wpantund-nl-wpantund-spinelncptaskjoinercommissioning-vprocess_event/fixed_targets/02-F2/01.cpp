#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "nl/wpantund/SpinelNCPTaskJoinerCommissioning.h"

extern "C" {
#include "nl/wpantund/SpinelNCPTaskJoinerCommissioning.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  nl::wpantund::SpinelNCPTaskJoinerCommissioning* obj =
      new nl::wpantund::SpinelNCPTaskJoinerCommissioning();

  const int event = stream.ConsumeIntegral<int>();
  va_list args;
  va_start(args, event);

  obj->vprocess_event(obj, event, args);

  va_end(args);
  delete obj;
  return 0;
}