#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "scan_entity.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  scan_entity((char *)data);
  return 0;
}

int main() {
  return 0;
}