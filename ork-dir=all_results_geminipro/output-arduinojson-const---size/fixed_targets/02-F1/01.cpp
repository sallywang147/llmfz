#include <cstring>
#include <vector>

extern "C" {
#include "Pack.h"
}

int Pack(const std::vector<unsigned char>& value, unsigned char* data, size_t size) {
  int error = Pack(value.data(), data, size);
  if (!error) {
    size_t len = value.size();
  }
  return 0;
}