#include <fuzzer/FuzzedDataProvider.h>
#include <libssh2.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libssh2
  libssh2_init(0);
  LIBSSH2_SESSION *session = libssh2_session_init();

  // Consume data for the parameters
  int type = stream.ConsumeIntegral<int>();
  std::string data_str = stream.ConsumeBytesAsString(stream.remaining_bytes() / 3);
  char *data_ptr = const_cast<char *>(data_str.c_str());
  size_t data_len = data_str.size();

  std::string public_key_str = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  char *public_key_ptr = const_cast<char *>(public_key_str.c_str());
  size_t public_key_len = public_key_str.size();

  // Generate an EC key for the private key
  EC_KEY *private_key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
  EC_KEY_generate_key(private_key);

  // Prepare an exchange_state
  kmdhgGPshakex_state_t exchange_state;

  // Call the function to fuzz
  ecdh_sha2_nistp(session, type, data_ptr, data_len, public_key_ptr, public_key_len, private_key, &exchange_state);

  // Cleanup
  EC_KEY_free(private_key);
  libssh2_session_free(session);
  libssh2_exit();

  return 0;
}