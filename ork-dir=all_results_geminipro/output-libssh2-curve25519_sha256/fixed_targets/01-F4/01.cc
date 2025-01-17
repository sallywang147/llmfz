#include <fuzzer/FuzzedDataProvider.h>
#include <libssh2.h>
#include <string.h>

extern "C" {
#include <kmdhgGPshakex.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t session_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char *session = new char[session_len];
  stream.ConsumeBytes(session, session_len);

  size_t data_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char *data = new char[data_len];
  stream.ConsumeBytes(data, data_len);

  size_t public_key_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char *public_key = new char[public_key_len];
  stream.ConsumeBytes(public_key, public_key_len);

  size_t private_key_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char *private_key = new char[private_key_len];
  stream.ConsumeBytes(private_key, private_key_len);

  size_t exchange_state_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char *exchange_state = new char[exchange_state_len];
  stream.ConsumeBytes(exchange_state, exchange_state_len);

  curve25519_sha256(session, data, data_len, public_key, private_key, exchange_state);

  delete[] session;
  delete[] data;
  delete[] public_key;
  delete[] private_key;
  delete[] exchange_state;

  return 0;
}
```

The following changes were made to the code:

- The `(struct _LIBSSH2_SESSION *)session` and `(kmdhgGPshakex_state_t *)exchange_state` casts were removed as they are not necessary.