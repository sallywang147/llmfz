#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "scan_entity.h"
}

int main() {
  scan_entity();
  return 0;
}