#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  SF_INFO sfinfo;
  sfinfo.frames = stream.ConsumeIntegral<int64_t>();
  sfinfo.samplerate = stream.ConsumeIntegral<int>();
  sfinfo.channels = stream.ConsumeIntegral<int>();
  sfinfo.format = stream.ConsumeIntegral<int>();
  sfinfo.sections = stream.ConsumeIntegral<int>();
  sfinfo.seekable = stream.ConsumeIntegral<int>();

  // We use a pipe to create a file descriptor because we need to ensure that the file descriptor is valid.
  // The file descriptor is only used to read data, so we only need to write data to the pipe.
  int pipefd[2];
  if (pipe(pipefd) != 0) {
    return 0;
  }

  // Write the remaining data to the pipe.
  std::vector<uint8_t> remaining_data = stream.ConsumeRemainingBytes<uint8_t>();
  write(pipefd[1], remaining_data.data(), remaining_data.size());
  close(pipefd[1]);

  // Use the read end of the pipe as the file descriptor.
  int fd = pipefd[0];

  // Choose a random mode and close_desc.
  int mode = stream.ConsumeIntegral<int>();
  int close_desc = stream.ConsumeIntegral<int>();

  struct sf_private_tag* sf = sf_open_fd(fd, mode, &sfinfo, close_desc);

  // We don't use the returned sf_private_tag*, so we can close the file descriptor now.
  close(fd);

  return 0;
}