#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include <hb.h>
}

int main() {
  hb_subset_preprocess();
  return 0;
}