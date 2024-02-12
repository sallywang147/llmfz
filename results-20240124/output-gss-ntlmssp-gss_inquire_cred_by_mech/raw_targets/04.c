 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gssapi.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc_struct mech_type = {0, NULL};
  gss_name_t name = GSS_C_NO_NAME;
  int initiator_lifetime = 0;
  int acceptor_lifetime = 0;
  int cred_usage = 0;

  gss_inquire_cred_by_mech(nullptr, &cred_handle, &mech_type, &name,
                            &initiator_lifetime, &acceptor_lifetime,
                            &cred_usage);

  return 0;
}