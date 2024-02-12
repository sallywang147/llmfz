#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <zlib.h>
#include <libgen.h>

#include "scanopt.h"

using namespace std;

extern "C" {
#include "scanopt.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *scanner = (char *)data;
  scanopt_init(&scanner, stdin, "usage");
  scanopt_usage(&scanner, stderr, "usage");
  return 0;
}