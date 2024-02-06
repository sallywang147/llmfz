#include <cups/cups.h>
#include "file.h"
#include "ipp-private.h"
#include "string-private.h"
#include <fcntl.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>

#define kMinInputLength 10
#define kMaxInputLength 10240

void LoadIPP(char *filename) {
  cups_file_t *fp;
  ipp_t *request;

  request = ippNew();
  fp = cupsFileOpen(filename, "r");

  ippReadIO(fp, (ipp_iocb_t)cupsFileRead, 1, NULL, request);

  cupsFileClose(fp);
  ippDelete(request);
}

extern "C" {
#include "file.h"
#include "ipp-private.h"
#include "string-private.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { /*cups/cups/fuzzipp.c*/

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 1;
  }

  char filename[256];

  sprintf(filename, "/tmp/libfuzzer.%d", getpid());
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }

  fwrite(Data, Size, 1, fp);
  fclose(fp);

  cups_http_t *http = cupsHttpNew();
  ipp_t *request = ippNew();
  cupsDoIORequest(http, request, filename, 0, 0);
  cupsHttpDelete(http);
  unlink(filename);

  return 0;
}