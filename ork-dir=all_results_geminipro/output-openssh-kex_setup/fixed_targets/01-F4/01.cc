#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "ssh.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string proposal = stream.ConsumeRemainingBytesAsString();
  ssh* ssh = ssh_new();
  int ret = kex_setup(ssh, proposal.c_str());
  ssh_free(ssh);
  return ret;
}