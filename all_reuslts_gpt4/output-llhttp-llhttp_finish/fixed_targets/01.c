#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "llhttp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  llhttp_t parser;
  llhttp_settings_t settings;

  llhttp_settings_init(&settings);
  llhttp_init(&parser, HTTP_BOTH, &settings);

  // Feed data to the parser.
  const char* buf = reinterpret_cast<const char*>(data);
  llhttp_errno_t error = llhttp_execute(&parser, buf, size);

  // Call the target function.
  int result = llhttp_finish(&parser);

  return 0;
}