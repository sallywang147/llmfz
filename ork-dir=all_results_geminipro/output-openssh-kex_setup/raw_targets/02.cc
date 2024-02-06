#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <ssh/ssh.h>
#include <ssh/kex.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a SSH struct.
  ssh_session session;
  ssh_options_set(&session.options, SSH_OPTIONS_HOST, "localhost");
  ssh_init(&session);

  // Create a proposal string.
  const std::string proposal = stream.ConsumeRemainingBytesAsString();
  char* proposal_cstr = strdup(proposal.c_str());

  // Call kex_setup.
  int result = kex_setup(&session, &proposal_cstr);

  // Clean up.
  ssh_finalize(&session);
  free(proposal_cstr);

  return result;
}