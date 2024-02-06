#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>

#include "sndfile.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int fd = memfd_create("fuzzer", MFD_CLOEXEC);
  if (fd == -1) {
    return 0;
  }
  write(fd, stream.data(), stream.size());
  lseek(fd, 0, SEEK_SET);

  SF_INFO sfinfo;
  sfinfo.format = 0;
  sfinfo.sections = 0;
  sfinfo.seekable = 0;

  int mode = stream.ConsumeIntegral<int>();
  int close_desc = stream.ConsumeIntegral<int>();

  struct sf_private_tag* sf = sf_open_fd(fd, mode, &sfinfo, close_desc);
  if (sf != nullptr) {
    sf_close(sf);
  }

  close(fd);
  return 0;
}