#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../htslib/sam.h"

#include <iostream>
#include <sstream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::stringstream stream(std::string(reinterpret_cast<const char*>(data), size));

  int min_shift = 0;
  stream >> min_shift;
  int nthreads = 0;
  stream >> nthreads;

  std::string fn;
  std::getline(stream, fn);
  std::string fnidx;
  std::getline(stream, fnidx);

  char *fn_c = new char[fn.length() + 1];
  strcpy(fn_c, fn.c_str());
  char *fnidx_c = new char[fnidx.length() + 1];
  strcpy(fnidx_c, fnidx.c_str());

  int ret = sam_index_build3(fn_c, fnidx_c, min_shift, nthreads);
  if (ret != 0) {
    abort();
  }

  delete[] fn_c;
  delete[] fnidx_c;

  return 0;
}