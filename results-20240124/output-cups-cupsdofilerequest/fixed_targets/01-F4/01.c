#include <cups/cups.h>

extern "C" {
#include <cups/http.h>
#include <cups/ipp.h>
}

int main() {
    http_t *http = httpConnectEncrypt(AF_UNSPEC, "localhost", 631);
    cupsDoFileRequest(http, NULL, "/jobs", "GET", NULL, 0, NULL);
    httpClose(http);
    return 0;
}