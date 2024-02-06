#include <fuzzer/FuzzedDataProvider.h>
#include <libsec.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize RSA private key
  struct RSApriv priv;
  priv.n = mpnew(0);
  priv.e = mpnew(0);
  priv.d = mpnew(0);
  priv.p = mpnew(0);
  priv.q = mpnew(0);
  priv.kp = mpnew(0);
  priv.kq = mpnew(0);
  priv.c2 = mpnew(0);

  // Generate random subject string
  std::string subj = stream.ConsumeRandomLengthString();
  char *subj_ptr = const_cast<char*>(subj.c_str());

  // Initialize validity period
  size_t valid = stream.ConsumeIntegral<size_t>();

  // Initialize certificate length
  int certlen = stream.ConsumeIntegral<int>();

  // Call the target function
  char* cert = X509gen(&priv, subj_ptr, &valid, &certlen);

  // Free the certificate
  free(cert);

  // Free the RSA private key
  mpfree(priv.n);
  mpfree(priv.e);
  mpfree(priv.d);
  mpfree(priv.p);
  mpfree(priv.q);
  mpfree(priv.kp);
  mpfree(priv.kq);
  mpfree(priv.c2);

  return 0;
}