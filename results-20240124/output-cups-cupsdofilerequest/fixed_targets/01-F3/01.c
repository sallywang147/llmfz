#include <cups/cups.h>

extern "C" {
#include <cups/http.h>
#include <cups/ipp.h>
}

int main() {
    cupsDoFileRequest("localhost", 631, "/jobs", "GET", NULL, 0, NULL);
    return 0;
}