#include <cups/cups.h>

extern "C" {
#include <cups/http.h>
#include <cups/ipp.h>
}

int main() {
    http_t *http = httpConnectEncrypt("localhost", 631, HTTP_ENCRYPT_IF_POSSIBLE);
    cupsDoFileRequest(http, NULL, "/jobs", "GET", NULL, 0);
    httpClose(http);
    return 0;
}