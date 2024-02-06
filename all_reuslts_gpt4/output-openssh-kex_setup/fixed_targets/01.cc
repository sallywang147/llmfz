#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

#include "ssh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct ssh *ssh = ssh_init();
  if (ssh == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t proposal_size = provider.ConsumeIntegralInRange<size_t>(0, 10); // Assuming we want a proposal of size at most 10
  char **proposal = (char **)malloc(sizeof(char *) * proposal_size);
  if (proposal == nullptr) {
    ssh_free(ssh);
    return 0;
  }

  for (size_t i = 0; i < proposal_size; ++i) {
    std::string proposal_item = provider.ConsumeRandomLengthString();
    proposal[i] = strdup(proposal_item.c_str());
    if (proposal[i] == nullptr) {
      for (size_t j = 0; j < i; ++j) {
        free(proposal[j]);
      }
      free(proposal);
      ssh_free(ssh);
      return 0;
    }
  }

  int ret = kex_setup(ssh, proposal);

  for (size_t i = 0; i < proposal_size; ++i) {
    free(proposal[i]);
  }
  free(proposal);
  ssh_free(ssh);

  return 0;
}