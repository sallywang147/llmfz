#include <stdio.h>
#include <stdlib.h>
#include <cups/cups.h>

extern "C" {
#include <ppd/ppd.h>
}

extern "C" char * _ppdCreateFromIPP(char * buffer, size_t bufsize, struct _ipp_s * supported);

int main() {
  char * buffer = NULL;
  size_t bufsize = 0;
  struct _ipp_s * supported = NULL;
  ppd_file_t *ppd = _ppdCreateFromIPP(buffer, bufsize, supported);
  if (!ppd) {
    fprintf(stderr, "Error creating PPD file.\n");
    return EXIT_FAILURE;
  }

  ppdFree(ppd);
  return EXIT_SUCCESS;
}