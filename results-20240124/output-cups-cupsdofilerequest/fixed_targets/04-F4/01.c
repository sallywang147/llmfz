#include <cups/cups.h>

extern "C" {
#include <cups/cups.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cupsDoFileRequest(NULL, NULL, NULL, data);
  return 0;
}

int main() {
  return 0;
}