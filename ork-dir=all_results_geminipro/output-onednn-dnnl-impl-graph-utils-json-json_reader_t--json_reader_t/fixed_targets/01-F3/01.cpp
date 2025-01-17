#include <fstream>
#include <iostream>
#include <string>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "json.hpp"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);

  char *fuzz_filename = "/tmp/fuzz.json";
  std::ofstream(fuzz_filename, std::ios::binary).write(input.c_str(), size);

  std::ifstream fs(fuzz_filename);
  dnnl::impl::graph::utils::json::json_reader_t read(&fs);
  dnnl::impl::graph::utils::json::json_reader_t *ptr = &read;
  delete ptr;
  // Call the destructor explicitly.
  read.~json_reader_t();

  return 0;
}