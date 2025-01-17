#include "../ini.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

int main(int argc, char **argv) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *str = (char *)data;
  ini_reader_string(str, size, NULL);
  return 0;
}

#endif