#include <fuzzer/FuzzedDataProvider.h>
#include "gss_ntlmssp.h"
#include <gssapi.h>
#include <krb5.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int minor_status;
  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc mech_type;
  gss_name_t name = GSS_C_NO_NAME;
  int initiator_lifetime;
  int acceptor_lifetime;
  int cred_usage;

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());
  void *data_ptr = bytes.data();
  mech_type.elements = data_ptr;
  mech_type.length = bytes.size();

  gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, &name, &initiator_lifetime, &acceptor_lifetime, &cred_usage);

  return 0;
}