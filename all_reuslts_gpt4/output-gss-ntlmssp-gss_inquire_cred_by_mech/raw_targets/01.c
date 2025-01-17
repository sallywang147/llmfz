#include "gss_ntlmssp.h"
#include <gssapi.h>
#include <krb5.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int minor_status;
  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc mech_type;
  gss_name_t name = GSS_C_NO_NAME;
  int initiator_lifetime;
  int acceptor_lifetime;
  int cred_usage;

  // Consume data for mech_type
  std::vector<uint8_t> mech_elements = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2);
  mech_type.length = mech_elements.size();
  mech_type.elements = mech_elements.data();

  // Call the function to fuzz
  gss_inquire_cred_by_mech(&minor_status, &cred_handle, &mech_type, &name, &initiator_lifetime, &acceptor_lifetime, &cred_usage);

  // Clean up
  gss_release_name(&minor_status, &name);
  gss_release_cred(&minor_status, &cred_handle);

  return 0;
}