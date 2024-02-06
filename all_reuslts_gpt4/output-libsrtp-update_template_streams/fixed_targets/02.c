#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  srtp_ctx_t_ session;
  srtp_policy_t policy;

  // Consume data for the session and policy objects
  size_t consumed = stream.ConsumeData(&session, sizeof(session));
  if (consumed != sizeof(session)) {
    return 0;
  }

  consumed = stream.ConsumeData(&policy, sizeof(policy));
  if (consumed != sizeof(policy)) {
    return 0;
  }

  // Call the function to fuzz
  update_template_streams(&session, &policy);

  return 0;
}