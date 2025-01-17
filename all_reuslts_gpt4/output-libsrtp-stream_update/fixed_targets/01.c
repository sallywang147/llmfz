#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct srtp_ctx_t_ session;
  struct srtp_policy_t policy;

  // Initialize session and policy with fuzzed data
  if (stream.remaining_bytes() < sizeof(session) + sizeof(policy)) {
    return 0;
  }
  stream.ConsumeData(&session, sizeof(session));
  stream.ConsumeData(&policy, sizeof(policy));

  // Call the target function
  stream_update(&session, &policy);

  return 0;
}