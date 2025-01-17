#include "file.h"
#include "string-private.h"
#include "ipp-private.h"
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define kMinInputLength 10
#define kMaxInputLength 10240

extern "C" {
#include "cups/cups.h"
}

void LoadIPP(char *filename){
    cups_file_t	*fp;
    ipp_t		*request;

    request = ippNew();
    fp = cupsFileOpen(filename, "r");

    ippReadIO(fp, (ipp_iocb_t)cupsFileRead, 1, NULL, request);

    cupsFileClose(fp);
    ippDelete(request);
}

extern int
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{/*cups/cups/fuzzipp.c*/

    if (Size < kMinInputLength || Size > kMaxInputLength){
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

    LoadIPP(filename);

    // Call the target function here
    cups_file_t *f = cupsFileOpen(filename, "r");
    ipp_t *request = ippNew();
    ippReadIO(f, (ipp_iocb_t)cupsFileRead, 1, NULL, request);
    cupsFileClose(f);
    cupsDoRequest(NULL, request, NULL);
    ippDelete(request);

    unlink(filename);

    return 0;
}