#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct srtp_ctx_t_ session;
  struct srtp_policy_t policy;

  // Initialize the session and policy with data from the fuzzer
  if (provider.remaining_bytes() < sizeof(session) + sizeof(policy)) {
    return 0;
  }
  provider.ConsumeData(&session, sizeof(session));
  provider.ConsumeData(&policy, sizeof(policy));

  srtp_stream_update(&session, &policy);

  return 0;
}