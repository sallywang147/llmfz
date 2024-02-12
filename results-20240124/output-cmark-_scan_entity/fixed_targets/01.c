#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "scan_entity.h"
}

int _scan_entity(char *buf) {
  return 0;
}

int main() {
  scan_entity();
  return 0;
}