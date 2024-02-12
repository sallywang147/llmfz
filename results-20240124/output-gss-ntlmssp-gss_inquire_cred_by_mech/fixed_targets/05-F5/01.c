#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <gssapi/gssapi.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const OM_uint32 minor_status = stream.ConsumeIntegral<OM_uint32>();
  gss_cred_id_t cred_handle =
      reinterpret_cast<gss_cred_id_t>(stream.ConsumeIntegral<uint64_t>());
  const gss_OID_desc_struct mech_type = {
      static_cast<OM_uint32>(stream.ConsumeIntegral<size_t>()),
      const_cast<char*>(stream.ConsumeRemainingBytesAsString().c_str())};
  gss_name_t name = nullptr;
  int initiator_lifetime = stream.ConsumeIntegral<int>();
  int acceptor_lifetime = stream.ConsumeIntegral<int>();
  int cred_usage = stream.ConsumeIntegral<int>();

  gss_inquire_cred_by_mech(&minor_status, cred_handle, &mech_type, &name,
                           &initiator_lifetime, &acceptor_lifetime,
                           &cred_usage);

  return 0;
}