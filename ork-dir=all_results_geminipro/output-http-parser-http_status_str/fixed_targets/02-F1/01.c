#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static const char *http_methods[] = {"GET", "POST", "HEAD", "PUT", "DELETE",
                                      "CONNECT", "OPTIONS", "TRACE", "PATCH"};
  static const char *http_versions[] = {"HTTP/0.9", "HTTP/1.0", "HTTP/1.1",
                                       "HTTP/2.0"};
  http_parser parser;
  http_parser_settings settings;
  http_parser_init(&parser, HTTP_REQUEST);
  settings.on_status = [](http_parser *p, const char *at, size_t length) -> int {
    http_status_str(atoi(at));
    return 0;
  };
  http_parser_execute(&parser, &settings, (const char *)data, size);
  return 0;
}