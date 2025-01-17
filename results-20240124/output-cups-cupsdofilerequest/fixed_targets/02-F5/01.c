#include <cups/cups.h>
#include <stdio.h>

extern "C" {
#include <cups/file.h>
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

  cups_file_t *fp = cupsFileOpen(argv[1], "r");
  if (!fp) {
    fprintf(stderr, "Error opening file %s\n", argv[1]);
    return 1;
  }

  cups_file_request_t *request = cupsFileRequestCreate(fp);
  if (!request) {
    fprintf(stderr, "Error creating file request\n");
    return 1;
  }

  cups_file_request_set_content_type(request, "application/octet-stream");

  cups_file_request_set_filename(request, argv[1]);

  cupsDoFileRequest(cupsGetDefault(), request, "/ipp/print");

  cupsFileRequestDestroy(request);

  cupsFileClose(fp);

  return 0;
}