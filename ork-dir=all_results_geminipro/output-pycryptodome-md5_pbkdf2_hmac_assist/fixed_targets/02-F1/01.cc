#include <fuzzer/FuzzedDataProvider.h>

#include <openssl/evp.h>
#include <openssl/hmac.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (!size)
    return 0;

  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> password = stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange(0, 128));
  std::vector<uint8_t> salt = stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange(0, 128));
  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t output_length = stream.ConsumeIntegral<size_t>();

  std::vector<uint8_t> result(output_length);

  EVP_MD_CTX *inner_ctx = EVP_MD_CTX_create();
  EVP_MD_CTX *outer_ctx = EVP_MD_CTX_create();

  EVP_DigestInit(inner_ctx, EVP_md5());
  EVP_DigestInit(outer_ctx, EVP_md5());

  PKCS5_PBKDF2_HMAC(
      (char *)password.data(), password.size(), (char *)salt.data(), salt.size(),
      iterations, EVP_md5(), output_length, (char *)result.data());

  EVP_MD_CTX_destroy(inner_ctx);
  EVP_MD_CTX_destroy(outer_ctx);

  return 0;
}