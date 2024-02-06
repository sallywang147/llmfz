#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "srtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  srtp_policy_t policy;
  srtp_init_policy(&policy);
  policy.ssrc.type = stream.ConsumeIntegral<uint8_t>();
  policy.ssrc.value = stream.ConsumeIntegral<uint32_t>();
  policy.key = stream.ConsumeBytes<uint8_t>(16);
  policy.ekt = stream.ConsumeBytes<uint8_t>(16);
  policy.window_size = stream.ConsumeIntegral<uint16_t>();
  policy.send_window_size = stream.ConsumeIntegral<uint16_t>();
  policy.auth_tag_len = stream.ConsumeIntegral<uint8_t>();
  policy.allow_repeat_tx = stream.ConsumeBool();
  policy.next_seq_num = stream.ConsumeIntegral<uint32_t>();
  policy.rtp_sender_auth_tag_len = stream.ConsumeIntegral<uint8_t>();
  policy.sec_serv = stream.ConsumeIntegral<uint32_t>();

  srtp_ctx_t session;
  srtp_init(&session);
  int ret = srtp_create(&session, &policy); // Change srtp_update to srtp_create
  if (ret != SRTP_OK) {
    fprintf(stderr, "srtp_create() failed with error code %d\n", ret);
    return 1;
  }

  srtp_close(&session);
  return 0;
}
```

The issue in the provided code is that it attempts to call `srtp_update` instead of `srtp_create` to initialize the SRTP session. This leads to the linker error because `srtp_update` is not defined in the SRTP library.

To fix the issue, replace `srtp_update` with `srtp_create` in the following line:

```c++
  int ret = srtp_create(&session, &policy); // Change srtp_update to srtp_create
```

With this change, the code should compile and run as expected.