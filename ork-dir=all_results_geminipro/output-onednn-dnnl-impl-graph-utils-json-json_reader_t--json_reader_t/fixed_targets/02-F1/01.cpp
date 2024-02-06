#include <fstream>
#include <iostream>
#include <string>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "json.hpp"

extern "C" {
#include "dnnl.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);

  char *fuzz_filename = "/tmp/fuzz.json";
  std::ofstream(fuzz_filename, std::ios::binary).write(input.c_str(), size);

  std::ifstream fs(fuzz_filename);
  dnnl::impl::graph::utils::json::json_reader_t read(&fs);
  try {
    read.~json_reader_t();
  } catch (...) {
  }

  return 0;
}