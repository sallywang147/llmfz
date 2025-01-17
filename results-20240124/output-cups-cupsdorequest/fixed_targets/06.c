#include "http-private.h"
#include "ipp-private.h"
#include <cups/cups.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    if (Size < 10 || Size > 10240)
        return 0;

    char filename[256];
    sprintf(filename, "/tmp/libfuzzer.%d", getpid());
    FILE *fp = fopen(filename, "wb");
    if (!fp)
        return 0;

    fwrite(Data, Size, 1, fp);
    fclose(fp);

    struct _ipp_s *request = ippNew();
    ippReadIO(fp, (ipp_iocb_t)cupsFileRead, 1, NULL, request);
    cupsFileClose((cups_file_t *)fp);
    unlink(filename);

    struct _http_s *http = httpConnectEncrypt(NULL, 631, HTTP_ENCRYPTION_NEVER);
    if (!http)
        return 0;

    struct _ipp_s *response = cupsDoRequest(http, request, "/printers/foobar");
    ippDelete(response);
    httpClose(http);

    ippDelete(request);

    return 0;
}