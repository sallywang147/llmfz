#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <gssapi.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gss_cred_id_struct* cred_handle = nullptr;
  gss_OID_desc_struct mech_type = {0, nullptr};
  gss_name_struct* name = nullptr;
  int initiator_lifetime = 0;
  OM_uint32 acceptor_lifetime = 0;
  int cred_usage = 0;
  OM_uint32 minor_status = 0;

  const size_t cred_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  if (cred_size) {
    cred_handle = reinterpret_cast<gss_cred_id_struct*>(
        malloc(cred_size));
    memset(cred_handle, 0, cred_size);
  }

  const size_t mech_type_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  if (mech_type_size) {
    mech_type.length = mech_type_size;
    mech_type.elements = reinterpret_cast<void*>(
        malloc(mech_type_size));
    stream.ConsumeBytes<uint8_t>(reinterpret_cast<uint8_t**>(&mech_type.elements),
                     mech_type_size);
  }

  const size_t name_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  if (name_size) {
    name = reinterpret_cast<gss_name_struct*>(malloc(name_size));
    memset(name, 0, name_size);
  }

  gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, name,
                           &initiator_lifetime, &acceptor_lifetime,
                           &cred_usage);

  if (cred_handle) {
    free(cred_handle);
  }
  if (mech_type.elements) {
    free(mech_type.elements);
  }
  if (name) {
    free(name);
  }

  return 0;
}