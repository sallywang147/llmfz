#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ssh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize ssh object
  struct ssh *ssh = ssh_init();
  if (ssh == nullptr) {
    return 0;
  }

  // Prepare proposal array
  char *proposal[PROPOSAL_MAX] = {0};

  // Fill the proposal array with strings from the fuzzing data
  for (int i = 0; i < PROPOSAL_MAX && stream.remaining_bytes() > 0; ++i) {
    proposal[i] = strdup(stream.ConsumeRandomLengthString().c_str());
    if (proposal[i] == nullptr) {
      for (int j = 0; j < i; ++j) {
        free(proposal[j]);
      }
      ssh_free(ssh);
      return 0;
    }
  }

  // Call the function to fuzz
  int result = kex_setup(ssh, proposal);

  // Cleanup
  for (int i = 0; i < PROPOSAL_MAX && proposal[i] != nullptr; ++i) {
    free(proposal[i]);
  }
  ssh_free(ssh);

  return 0;
}