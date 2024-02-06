#include <gssapi/gssapi.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <stdio.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc_struct mech_type = {0, 0};
  gss_name_t name = GSS_C_NO_NAME;
  int initiator_lifetime = 0;
  int acceptor_lifetime = 0;
  int cred_usage = 0;
  OM_uint32 minor_status = 0;

  // Consume the input data and set the input parameters.
  std::vector<uint8_t> cred_handle_bytes = fdp.ConsumeBytes<uint8_t>(fdp.ConsumeIntegralInRange(0, 1024));
  cred_handle = (gss_cred_id_t)cred_handle_bytes.data();

  std::vector<uint8_t> mech_type_oid = fdp.ConsumeBytes<uint8_t>(fdp.ConsumeIntegralInRange(0, 1024));
  mech_type.length = mech_type_oid.size();
  mech_type.elements = mech_type_oid.data();

  // Call the function to be fuzzed.
  OM_uint32 major_status = gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, &name, &initiator_lifetime, &acceptor_lifetime, &cred_usage);

  // Check the status code.
  if (major_status != GSS_S_COMPLETE) {
    fprintf(stderr, "gss_inquire_cred_by_mech failed: %s\n", gss_error_string(minor_status));
    return 1;
  }

  // Consume the remaining input data.
  std::vector<uint8_t> remaining_bytes = fdp.ConsumeRemainingBytes();

  return 0;
}