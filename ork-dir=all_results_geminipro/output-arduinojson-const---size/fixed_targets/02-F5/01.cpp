#include <cstring>
#include <vector>

extern "C" {
#include "Pack.h"
}

int Pack(unsigned char* data, size_t size, const std::vector<unsigned char>& value) {
  int error = Pack(data, size, value.data(), value.size());
  if (!error) {
    size_t len = value.size();
  }
  return error;
}