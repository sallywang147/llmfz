 #include "file.h"
#include "string-private.h"
#include "ipp-private.h"
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define kMinInputLength 10
#define kMaxInputLength 10240

void LoadIPP(char *filename){
    cups_file_t	*fp;
    ipp_t		*request;

    request = ippNew();
    fp = cupsFileOpen(filename, "r");

    ippReadIO(fp, (ipp_iocb_t)cupsFileRead, 1, NULL, request);

    cupsFileClose(fp);
    ippDelete(request);
}

extern struct _ipp_s *
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{/*cups/cups/fuzzipp.c*/

    if (Size < kMinInputLength || Size > kMaxInputLength){
      return NULL;
    }

    char filename[256];

    sprintf(filename, "/tmp/libfuzzer.%d", getpid());
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        return NULL;
    }

    fwrite(Data, Size, 1, fp);
    fclose(fp);

    char *resource = (char *) "/printers/foo";

    int infile = open(filename, O_RDONLY);
    if (infile == -1) {
      return NULL;
    }

    int outfile = open("/dev/null", O_WRONLY);
    if (outfile == -1) {
      close(infile);
      return NULL;
    }

    struct _http_s *http = NULL;
    struct _ipp_s *request = ippNewRequest(IPP_OP_PRINT_JOB);

    cupsDoIORequest(http, request, resource, infile, outfile);

    close(infile);
    close(outfile);
    unlink(filename);

    return request;
}