#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int wgnutls_read(int fd, char * buf, int bufsize, char * arg, double timeout);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We don't actually have a file descriptor to read from, so we'll just use an invalid one.
  int fd = -1;

  // We'll allocate a buffer of a random size between 0 and the remaining number of bytes.
  int bufsize = stream.ConsumeIntegralInRange<int>(0, stream.remaining_bytes());
  char* buf = new char[bufsize];

  // We'll consume a string for the "arg" parameter.
  std::string arg = stream.ConsumeRandomLengthString();
  
  // We'll consume a double for the "timeout" parameter.
  double timeout = stream.ConsumeFloatingPoint<double>();

  // Call the function under test.
  wgnutls_read(fd, buf, bufsize, const_cast<char*>(arg.c_str()), timeout);

  delete[] buf;

  return 0;
}