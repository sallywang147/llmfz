#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "srtp.h"

extern "C" {
#include <srtp/srtp.h>
}

extern "C" int update_template_streams(srtp_ctx_t_ session, srtp_policy_t_ policy);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  srtp_policy_t policy;
  srtp_init();
  srtp_policy_init(&policy);
  srtp_policy_parse(&policy, stream.ConsumeRemainingBytesAsString().c_str(),
                    stream.remaining_bytes());
  srtp_ctx_t_ session;
  srtp_create(&session, &policy);
  int ret = update_template_streams(&session, &policy);
  srtp_policy_destroy(&policy);
  srtp_destroy(&session);
  srtp_shutdown();
  return ret;
}