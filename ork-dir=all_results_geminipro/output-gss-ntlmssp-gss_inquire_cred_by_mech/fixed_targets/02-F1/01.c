#include <gssapi.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  OM_uint32 minor_status;
  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc_struct mech_type = {0, 0};
  gss_name_t name = GSS_C_NO_NAME;
  int initiator_lifetime = 0;
  int acceptor_lifetime = 0;
  int cred_usage = 0;

  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 1024));
  void *data_ptr = bytes.data();

  gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, &name, &initiator_lifetime,
                          &acceptor_lifetime, &cred_usage);
  return 0;
}