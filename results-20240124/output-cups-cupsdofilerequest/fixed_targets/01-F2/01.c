#include <cups/cups.h>

int main() {
    cupsDoFileRequest("localhost", 631, "/jobs", "GET", NULL, 0, NULL);
    return 0;
}