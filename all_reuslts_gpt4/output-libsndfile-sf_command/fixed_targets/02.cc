#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the library
  SF_INFO sfinfo = {};
  sfinfo.channels = 1;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
  SNDFILE *sndfile = sf_open_fd(0, SFM_WRITE, &sfinfo, 0);

  if (sndfile == nullptr) {
    return 0;
  }

  // Consume data for the command and datasize parameters
  int command = stream.ConsumeIntegral<int>();
  int datasize = stream.ConsumeIntegral<int>();

  // Consume data for the data parameter
  std::string data_str = stream.ConsumeBytesAsString(datasize);
  char *data_ptr = const_cast<char*>(data_str.c_str());

  // Call the target function
  sf_command(sndfile, command, data_ptr, datasize);

  // Close the file
  sf_close(sndfile);

  return 0;
}