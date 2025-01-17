#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <gssapi.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gss_cred_id_t cred_handle = GSS_C_NO_CREDENTIAL;
  gss_OID_desc_struct mech_type = {0, 0};
  gss_name_t name;
  int initiator_lifetime;
  int acceptor_lifetime;
  int cred_usage;
  OM_uint32 minor_status;

  gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, &name,
                            &initiator_lifetime, &acceptor_lifetime,
                            &cred_usage);

  return 0;
}