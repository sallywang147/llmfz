#include <algorithm>
#include <gssapi/gssapi.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  OM_uint32 minor_status;
  gss_cred_id_t cred_handle;
  gss_OID_desc_struct mech_type;
  gss_name_t name;
  OM_uint32 initiator_lifetime;
  OM_uint32 acceptor_lifetime;
  int cred_usage;
  gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, &name,
                           &initiator_lifetime, &acceptor_lifetime, &cred_usage);
  return 0;
}