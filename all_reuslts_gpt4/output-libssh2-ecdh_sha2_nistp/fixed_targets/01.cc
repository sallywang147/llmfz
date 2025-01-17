#include <fuzzer/FuzzedDataProvider.h>
#include <libssh2.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libssh2
  libssh2_init(0);

  // Initialize a libssh2 session
  struct _LIBSSH2_SESSION *session = libssh2_session_init();
  if (!session) {
    libssh2_exit();
    return 0;
  }

  // Define and initialize parameters for ecdh_sha2_nistp
  int type = stream.ConsumeIntegral<int>();
  std::string data_str = stream.ConsumeRandomLengthString();
  char *data_ptr = const_cast<char*>(data_str.c_str());
  size_t data_len = data_str.size();
  std::string public_key_str = stream.ConsumeRandomLengthString();
  char *public_key = const_cast<char*>(public_key_str.c_str());
  size_t public_key_len = public_key_str.size();

  // Generate a private key
  EC_KEY *private_key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
  if (!private_key) {
    libssh2_session_free(session);
    libssh2_exit();
    return 0;
  }
  EC_KEY_generate_key(private_key);

  // Initialize exchange_state
  struct kmdhgGPshakex_state_t exchange_state;

  // Call ecdh_sha2_nistp
  ecdh_sha2_nistp(session, type, data_ptr, data_len, public_key, public_key_len, private_key, &exchange_state);

  // Clean up
  EC_KEY_free(private_key);
  libssh2_session_free(session);
  libssh2_exit();

  return 0;
}