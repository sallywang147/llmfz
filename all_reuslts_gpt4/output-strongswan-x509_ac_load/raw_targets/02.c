#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "x509_ac.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int type = stream.ConsumeIntegral<int>();

  struct __va_list_tag args;
  args.gp_offset = stream.ConsumeIntegral<unsigned int>();
  args.fp_offset = stream.ConsumeIntegral<unsigned int>();
  args.overflow_arg_area = (void *)stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();
  args.reg_save_area = (void *)stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();

  struct x509_ac_t * result = x509_ac_load(type, &args);

  if (result != NULL) {
    // Do something with result
    // ...
    free(result);
  }

  return 0;
}