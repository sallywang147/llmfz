#include <stdio.h>
#include <stdlib.h>
#include <cups/cups.h>

extern "C" {
#include <ppd/ppd.h>
}

int main() {
  ppd_file_t *ppd = ppdCreateFromIPP(NULL);
  if (!ppd) {
    fprintf(stderr, "Error creating PPD file.\n");
    return EXIT_FAILURE;
  }

  ppdFree(ppd);
  return EXIT_SUCCESS;
}