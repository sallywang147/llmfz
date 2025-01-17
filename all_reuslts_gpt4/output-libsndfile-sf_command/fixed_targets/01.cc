#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize sndfile
  SF_INFO sfinfo = {};
  sfinfo.channels = 2;
  sfinfo.samplerate = 44100;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  SNDFILE *sndfile = sf_open_fd(fileno(tmpfile()), SFM_RDWR, &sfinfo, SF_FALSE);
  if (sndfile == nullptr) {
    return 0;
  }

  // Extract command
  int command = stream.ConsumeIntegral<int>();

  // Extract datasize
  int datasize = stream.ConsumeIntegralInRange<int>(0, 1000);

  // Extract data
  std::vector<char> data_vector = stream.ConsumeBytes<char>(datasize);

  // Call the function under test
  sf_command(sndfile, command, data_vector.data(), datasize);

  // Clean up
  sf_close(sndfile);

  return 0;
}