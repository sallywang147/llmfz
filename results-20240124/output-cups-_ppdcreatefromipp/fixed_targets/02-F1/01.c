#include "file.h"
#include "string-private.h"
#include "ipp-private.h"
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

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
#include "cups/file.h"
#include "cups/ipp-private.h"
#include "cups/ipp.h"
#include "cups/ppd.h"

char *
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{/*cups/cups/fuzzipp.c*/

    if (Size < kMinInputLength || Size > kMaxInputLength) {
        return nullptr;
    }

    char filename[256];

    sprintf(filename, "/tmp/libfuzzer.%d", getpid());
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        return nullptr;
    }

    fwrite(Data, Size, 1, fp);
    fclose(fp);

    LoadIPP(filename);
    unlink(filename);

    return _ppdCreateFromIPP(nullptr, 0, nullptr);
}
}