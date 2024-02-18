#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <gssapi.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gss_cred_id_t cred_handle;
  gss_OID mech_type = {0, NULL};
  gss_name_t name = GSS_C_NO_NAME;
  OM_uint32 initiator_lifetime = 0;
  OM_uint32 acceptor_lifetime = 0;
  int cred_usage = 0;

  gss_inquire_cred_by_mech(&mech_type, &cred_handle, nullptr, &name,
                            &initiator_lifetime, &acceptor_lifetime,
                            &cred_usage);

  return 0;
}