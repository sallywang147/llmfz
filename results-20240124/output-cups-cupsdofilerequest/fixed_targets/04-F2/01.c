#include <cups/cups.h>

extern "C" {
#include <cups/cups.h>
}

int main() {
  cupsDoFileRequest(NULL, NULL, NULL, 0, NULL, NULL);
  return 0;
}