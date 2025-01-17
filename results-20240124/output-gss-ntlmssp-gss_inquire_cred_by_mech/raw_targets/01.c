 #include <gssapi.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int minor_status = 0;
  gss_cred_id_struct *cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc_struct mech_type = {0, NULL};
  gss_name_struct **name = NULL;
  int initiator_lifetime = 0;
  int acceptor_lifetime = 0;
  int cred_usage = 0;

  gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, name,
                           &initiator_lifetime, &acceptor_lifetime,
                           &cred_usage);

  return 0;
}