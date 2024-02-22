#include <boost/json.hpp>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

using namespace boost::json;

void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  value v;
  parse(&v, (char*)data, size);
}