#include <cups/cups.h>

extern "C" {
#include <cups/cups.h>
}

int main() {
  cupsDoFileRequest(NULL, NULL, NULL, NULL);
  return 0;
}