#include <iostream>
#include <string>
#include <boost/json.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/gzip.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/array.hpp>

extern "C" {
#include <stdint.h>
}

using namespace std;
using namespace boost::iostreams;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  boost::json::value v;
  boost::json::parse(&v, (char *)data, size);
  return 0;
}